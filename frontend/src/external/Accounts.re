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
  "refreshSession": unit => Js.Promise.t(Js.Nullable.t(string)),
  "getUser": unit => Js.Promise.t(Js.Nullable.t(User.Model.Fragment.Fields.t)),
  "sendVerficationEmail": string => Js.Promise.t(unit),
  "logout": unit => Js.Promise.t(unit),
  "login": loginInput => Js.Promise.t(unit),
  "requestPasswordReset": string => Js.Promise.t(unit),
  "resetPassword": (string, string) => Js.Promise.t(unit),
  "createUser": (createUserInput) => Js.Promise.t(unit),
  "getTwoFactorSecret": unit => Js.Promise.t(string),
  "twoFactorSet": (string, string) => Js.Promise.t(unit),
  "verifyEmail":  (string) => Js.Promise.t(unit),
};
[@bs.new] [@bs.module "apollo-accounts-password-client"] external createAccountClient : (ApolloClient.generatedApolloClient) => t = "default";
let accountClient = createAccountClient(Client.authInstance);
Js.log("account Client");
Js.log(accountClient);
/* [%debugger]; */
