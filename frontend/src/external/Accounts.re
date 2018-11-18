type createUserInput = {
  .
  "email": string,
  "password": string,
};

type userInput = {
  .
  "email": string,
};

type loginInput = {
  .
  "code": string,
  "password": string,
  "user": userInput,
};

type t = {
  .
  [@bs.meth] "refreshSession": unit => Js.Promise.t(Js.Nullable.t(string)),
  [@bs.meth] "getUser": unit => Js.Promise.t(Js.Nullable.t(User.Model.Fragment.Fields.t)),
  [@bs.meth] "sendVerficationEmail": string => Js.Promise.t(unit),
  [@bs.meth] "logout": unit => Js.Promise.t(unit),
  [@bs.meth] "login": loginInput => Js.Promise.t(unit),
  [@bs.meth] "requestPasswordReset": string => Js.Promise.t(unit),
  [@bs.meth] "resetPassword": (string, string) => Js.Promise.t(unit),
  [@bs.meth] "createUser": (createUserInput) => Js.Promise.t(unit),
  [@bs.meth] "getTwoFactorSecret": unit => Js.Promise.t(string),
  [@bs.meth] "twoFactorSet": (string, string) => Js.Promise.t(unit),
  [@bs.meth] "verifyEmail":  (string) => Js.Promise.t(unit),
};
[@bs.new] [@bs.module "apollo-accounts-password-client"] external createAccountClient : (ApolloClient.generatedApolloClient) => t = "default";
let accountClient = createAccountClient(Client.authInstance);

type state = {
  id: string,
};

type action =
  | UpdateUserId(string)
  | RefreshSession
  | SendVerficationEmail(string)
  | Logout
  | Login(loginInput)
  | RequestPasswordReset(string)
  | ResetPassword(string, string)
  | CreateUser(createUserInput)
  | GetTwoFactorSecret
  | TwoFactorSet(string, string)
  | VerifyEmail(string);

let component = ReasonReact.reducerComponent("Accounts");

let getUserPromise = (promise, send) => 
promise
|> Js.Promise.then_((_) => accountClient##getUser())
|> Js.Promise.then_(u => {
  Js.log("user promise u =");
  Js.log(u);
  u
  |> Js.Nullable.toOption(_)
  |> Belt.Option.mapWithDefault(_, "", (u) => u##id)
  |> (id) => UpdateUserId(id)
  |> send
  |> Js.Promise.resolve
})
|> ignore;

let make = children => {
  ...component,
  initialState: () => ({id: ""}),
  reducer: (action, _state: state) =>
    switch (action) {
    | UpdateUserId(id) => ReasonReact.Update({id: id})
    | RefreshSession => ReasonReact.SideEffects(({send}) => accountClient##refreshSession() |> getUserPromise(_, send))
    | SendVerficationEmail(verify) => ReasonReact.SideEffects(({send}) => accountClient##sendVerficationEmail(verify) |> getUserPromise(_, send))
    | Logout => ReasonReact.SideEffects(({send}) => accountClient##logout() |> getUserPromise(_, send))
    | Login(loginInput) => {
      Js.log("running login loginInput =");
      Js.log(loginInput);
      ReasonReact.SideEffects(({send}) => accountClient##login(loginInput) |> getUserPromise(_, send))
    }
    | RequestPasswordReset(reset) => ReasonReact.SideEffects(({send}) => accountClient##requestPasswordReset(reset) |> getUserPromise(_, send))
    | ResetPassword(email, password) => ReasonReact.SideEffects(({send}) => accountClient##resetPassword(email, password) |> getUserPromise(_, send))
    | CreateUser(createUserInput) => ReasonReact.SideEffects(({send}) => accountClient##createUser(createUserInput) |> getUserPromise(_, send))
    | GetTwoFactorSecret => ReasonReact.SideEffects(({send}) => accountClient##getTwoFactorSecret() |> getUserPromise(_, send))
    | TwoFactorSet(f1, f2) => ReasonReact.SideEffects(({send}) => accountClient##twoFactorSet(f1, f2) |> getUserPromise(_, send))
    | VerifyEmail(verify) => ReasonReact.SideEffects(({send}) => accountClient##verifyEmail(verify) |> getUserPromise(_, send))
    },
  render: self =>
    <div>
      {
        children(
          ~accountSend=(action => {
            Js.log("running account send");
            self.send(action)
          }),
          ~user=accountClient##getUser()
        )
      }
    </div>
};
