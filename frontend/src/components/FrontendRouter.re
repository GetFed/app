

let defaultState = () => {
  let url = ReasonReact.Router.dangerouslyGetInitialUrl();
  Js.log("url = %j");
  Js.log(url);
  (url.path)
  |> PathIds.pathToIds
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
      | Some(url) => url |> Utils.Dom.parseUrl |> PathIds.pathToIds
      | None => defaultState()
      },
  }),
  reducer: (action, _state: state) =>
    switch (action) {
    | RouteInfo(pathIds) => ReasonReact.Update({pathIds: pathIds})
    | NoOp => ReasonReact.NoUpdate
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(RouteInfo(PathIds.pathToIds(url.path))));
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: ({state: {pathIds}}) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <Page.Main pathIds />
    | {giftsId: Some(_)} => <Page.Main pathIds />
    | {supportId: Some(_)} => <Page.Main pathIds />
    | {menuId: Some(_)} => <Page.Main pathIds />
    | {subscriptionId: Some(_)} => <Page.Main pathIds />
    | {adminId: Some(_)} => <Page.Main pathIds />
    | {aboutUsId: Some(_)} => <Page.Main pathIds />
    | _ => <Page.Main pathIds />
    }
};

