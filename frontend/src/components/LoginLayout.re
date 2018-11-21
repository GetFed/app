let css = Css.css;
let tw = Css.tw;
let loginLayoutClass = [%bs.raw
  {| css(tw` bg-green h-64`)|}
];

type state = {
  email: string,
  password: string,
};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string);

let component = ReasonReact.reducerComponent("LoginLayout");

let make = (~accountSend, ~afterLoginClick, _children) => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmail(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    },
  render: self =>
    <div className=loginLayoutClass>
      <TextInput value=self.state.email onTextChange=((email) => self.send(UpdateEmail(email)) |> Js.Promise.resolve) placeholder="Email"/>
      <TextInput value=self.state.password onTextChange=((password) => self.send(UpdatePassword(password)) |> Js.Promise.resolve) type_="password" placeholder="Password"/>
      <Button
        onClick=(() =>
          {
            accountSend(Accounts.AccountWithPromise(
              Login({
                "password": self.state.password,
                "user": { "email": self.state.email },
                "code": ""
              }),
              Js.Promise.make((~resolve, ~reject) => {
                afterLoginClick();
                resolve(. true);
              })
            ))
          })
        theme=CTA
      >
        {ReasonReact.string("Login abc")}
      </Button>
    </div>
  };
