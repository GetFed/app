let css = Css.css;
let tw = Css.tw;

let loginLayoutClass = [%bs.raw
  {| css(tw`
    bg-white
    h-full
    w-64
    px-4
    py-32
    flex
    flex-col
    justify-center
  `)|}
];

let loginButtons = [%bs.raw
{| css(tw`
  flex
  justify-between
`)|}
];

let loginButton = [%bs.raw
{| css(tw`
`)|}
];

let loginTextInput = [%bs.raw
{| css(tw`
  mb-4
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
              onClick=((_) => loginButtonOnClick(self.state, accountSend, successClick))
            >
              {ReasonReact.string("Sign In")}
            </FedButton>
          </div>
          <div>
            <FedButton
              color=GREY
              onClick=((_) => loginButtonOnClick(self.state, accountSend, successClick))
            >
              {ReasonReact.string("Join (x)")}
            </FedButton>
          </div>
        </div>
      </div>
  };
