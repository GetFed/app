let css = Css.css;
let tw = Css.tw;

let loginLayoutClass = [%bs.raw
  {| css(tw`
    bg-white
    h-full
    px-32
    flex
    flex-col
    justify-center
    w-full
    sm:w-2/3
    sm:h-5/6
    md:w-1/2
  `)|}
];

let loginLayoutSigninText = [%bs.raw
{| css(tw`
  h-32
  flex
  justify-center
  items-center
  text-green-darker
  text-4xl
`)|}
];

let loginButtons = [%bs.raw
{| css(tw`
  flex
  justify-between
  mb-16
`)|}
];

let loginButton = [%bs.raw
{| css(tw`
`)|}
];

let loginTextInput = [%bs.raw
{| css(tw`
  mb-6
`)|}
];

let loginLayoutCenterTextClass = [%bs.raw
{| css(tw`
  flex
  justify-center
  items-center
`)|}
];

type state = {
  email: string,
  password: string,
};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string);

let component = ReasonReact.reducerComponent("LoginLayout");

let loginButtonOnClick = (state : state, accountSend, successClick) =>
  {
    accountSend(Accounts.AccountWithPromise(
      Login({
        "password": state.password,
        "user": { "email": state.email },
        "code": ""
      }),
      (userId : option(string)) =>
        Js.Promise.make((~resolve, ~reject) => {
          /* TODO OVER HERE HANDLE ERRORS FOR LOGIN */
          userId !== None ? successClick() : ();
          resolve(. true);
        })
    ))
  };



let make = (~accountSend, ~successClick, _children) => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmail(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    },
  render: self =>
      <div className=loginLayoutClass>
        <div className=loginLayoutSigninText>
          {ReasonReact.string("Sign In")}
        </div>
        <div className=loginTextInput>
          <FedTextInput
            value=self.state.email
            onTextChange=((email) => self.send(UpdateEmail(email)) |> Js.Promise.resolve)
            placeholder="Email"
          />
        </div>
        <div className=loginTextInput>
          <FedTextInput
            value=self.state.password
            onTextChange=((password) => self.send(UpdatePassword(password)) |> Js.Promise.resolve)
            type_="password"
            placeholder="Password"
          />
        </div>
        <div className=loginButtons>
          <div>
            <FedButton
              size=LARGE
              onClick=((_) => loginButtonOnClick(self.state, accountSend, successClick))
            >
              {ReasonReact.string("Sign In")}
            </FedButton>
          </div>
          <div>
            <FedButton
              size=LARGE
              color=GREY
              onClick=((_) => loginButtonOnClick(self.state, accountSend, successClick))
            >
              {ReasonReact.string("Join (x)")}
            </FedButton>
          </div>
        </div>
        <div className=loginLayoutCenterTextClass>
          <div>
            <div className=loginLayoutCenterTextClass>
              {ReasonReact.string("Forgot your password?")}
            </div>
            <a className=loginLayoutCenterTextClass>
              {ReasonReact.string("Click here")}
            </a>
          </div>
        </div>
      </div>
  };
