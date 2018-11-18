let accessTokenNamespace = "accounts:accessToken";
let refreshTokenNamespace = "accounts:refreshToken";
let sessionNamespace = "sessionId";
let viewNamespace = "viewId";

let saveAuth = (token, value) =>
  switch (value) {
  | None => ()
  | Some(authorizationToken) =>
    Dom.Storage.localStorage
    |> Dom.Storage.setItem(token, authorizationToken)
  };

let getAuth = (token) =>
  Document.isBrowser() ?
    Dom.Storage.localStorage |> Dom.Storage.getItem(token) :
    None;
    
let replaceToken = (token, value) =>{
  saveAuth(token, value);

  getAuth(token)
  |> Belt.Option.getWithDefault(_, "");
};

let replaceTokenIfDoesNotExist = (token, value) =>{
  switch(getAuth(token)){
  | None => replaceToken(token, value)
  | Some(tokenVal) => tokenVal
  };
};