
type myAccountId = option(option(string));
type giftsId = option(option(string));
type supportId = option(option(string));
type menuId = option(option(string));

type pathIds = {
  myAccountId,
  giftsId,
  supportId,
  menuId,
};
let defaultIds = {
  myAccountId: None,
  giftsId: None,
  supportId: None,
  menuId: None,
};

let stringEmptyStringOptional = (possibleEmptyString: string) : option(string) =>
  possibleEmptyString == "" ? None : Some(possibleEmptyString);
 
let urlToIds = (url: ReasonReact.Router.url): pathIds =>
  switch (url.path) {
  | ["my-account", myAccountId] => {...defaultIds, myAccountId: Some(stringEmptyStringOptional(myAccountId))}
  | ["my-account"] => {...defaultIds, myAccountId: Some(None)}
  | ["gifts", giftsId] => {...defaultIds, giftsId: Some(stringEmptyStringOptional(giftsId))}
  | ["gifts"] => {...defaultIds, giftsId: Some(None)}
  | ["support", supportId] => {...defaultIds, supportId: Some(stringEmptyStringOptional(supportId))}
  | ["support"] => {...defaultIds, supportId: Some(None)}
  | ["menu", menuId] => {...defaultIds, menuId: Some(stringEmptyStringOptional(menuId))}
  | ["menu"] => {...defaultIds, menuId: Some(None)}
  | _ => defaultIds
  };

let defaultState = () => ReasonReact.Router.dangerouslyGetInitialUrl() |> urlToIds;

type state = {
  ids: pathIds
};

type action =
  | RouteInfo(pathIds)
  | NoOp;

let component = ReasonReact.reducerComponent("FrontendRouter");

let make = (_children) => {
  ...component,
  initialState: () => {ids: defaultState()},
  reducer: (action, _state: state) =>
    switch (action) {
    | RouteInfo(ids) => ReasonReact.Update({ids: ids })
    | NoOp => ReasonReact.NoUpdate
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(RouteInfo(urlToIds(url))));
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: (self) =>
    switch (self.state.ids) {
    | {myAccountId: Some(_)} => <Page.Home />
    | {giftsId: Some(_)} => <Page.Home />
    | {supportId: Some(_)} => <Page.Home />
    | {menuId: Some(_)} => <Page.Home />
    | _ => <Page.Home />
    }
};

