let accessTokenNamespace = "accounts:accessToken";
let refreshTokenNamespace = "accounts:refreshToken";
let saveAuth = () =>
  switch (Document.getHash()) {
  | None => ()
  | Some(authorizationToken) =>
    Dom.Storage.localStorage
    |> Dom.Storage.setItem(accessTokenNamespace, authorizationToken)
  };

let getAuth = () =>
  Document.isBrowser() ?
    Dom.Storage.localStorage |> Dom.Storage.getItem(accessTokenNamespace) :
    None;