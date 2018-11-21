let stringEmptyStringOptional = (possibleEmptyString: string) : option(string) =>
  possibleEmptyString == "" ? None : Some(possibleEmptyString);
 
let pathToIds = (path: list(string)): PathIds.t =>
  switch (path) {
  | ["my-account", myAccountId] => {...PathIds.default, myAccountId: Some(stringEmptyStringOptional(myAccountId))}
  | ["my-account"] => {...PathIds.default, myAccountId: Some(None)}
  | ["gifts", giftsId] => {...PathIds.default, giftsId: Some(stringEmptyStringOptional(giftsId))}
  | ["gifts"] => {...PathIds.default, giftsId: Some(None)}
  | ["support", supportId] => {...PathIds.default, supportId: Some(stringEmptyStringOptional(supportId))}
  | ["support"] => {...PathIds.default, supportId: Some(None)}
  | ["menu", menuId] => {...PathIds.default, menuId: Some(stringEmptyStringOptional(menuId))}
  | ["menu"] => {...PathIds.default, menuId: Some(None)}
  | ["subscribe"] => {...PathIds.default, subscriptionId: Some(None)}
  | ["admin"] => {...PathIds.default, adminId: Some(None)}
  | _ => PathIds.default
  };

let defaultState = () => {
  let url = ReasonReact.Router.dangerouslyGetInitialUrl();
  Js.log("url = %j");
  Js.log(url);
  (url.path)
  |> pathToIds
};

type state = {
  pathIds: PathIds.t
};

type action =
  | RouteInfo(PathIds.t)
  | NoOp;

let component = ReasonReact.reducerComponent("FrontendRouter");

let make = (~initialUrl: option(string), _children) => {
  ...component,
  initialState: () => ({
    pathIds: 
      switch (initialUrl) {
      | Some(url) => url |> Utils.Dom.parseUrl |> pathToIds
      | None => defaultState()
      },
  }),
  reducer: (action, _state: state) =>
    switch (action) {
    | RouteInfo(pathIds) => ReasonReact.Update({pathIds: pathIds})
    | NoOp => ReasonReact.NoUpdate
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(RouteInfo(pathToIds(url.path))));
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: ({state: {pathIds}}) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <Page.Home pathIds />
    | {giftsId: Some(_)} => <Page.Home pathIds />
    | {supportId: Some(_)} => <Page.Home pathIds />
    | {menuId: Some(_)} => <Page.Home pathIds />
    | {subscriptionId: Some(_)} => <Page.Home pathIds />
    | {adminId: Some(_)} => <Page.Home pathIds />
    | _ => <Page.Home pathIds />
    }
};

