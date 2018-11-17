type classroomId = option(string);
type studentId = option(string);
type testId = option(string);

type ids = {
  classroomId,
  studentId,
  testId,
};

type state = {ids};

type action =
  | RouteInfo(classroomId, studentId, testId)
  | NoOp;

let urlToIds =
    (url: ReasonReact.Router.url): option((classroomId, studentId, testId)) =>
  switch (url.path) {
  | ["classroom", classroomId, "student", studentId, "test", testId] =>
    Some((Some(classroomId), Some(studentId), Some(testId)))
  | ["preview", testId] => Some((None, None, Some(testId)))
  | _ => None
  };

let component = ReasonReact.reducerComponent("App");

let defaultState = () =>
  ReasonReact.Router.dangerouslyGetInitialUrl()
  |> urlToIds
  |> Belt.Option.mapWithDefault(
       _,
       {
         ids: {
           classroomId: None,
           studentId: None,
           testId: None,
         },
       },
       ((classroomId, studentId, testId)) =>
       {
         ids: {
           classroomId,
           studentId,
           testId,
         },
       }
     );
let make = /*~title, ~initialUrl, ~server : bool, */ _children => {
  ...component,
  initialState: () => defaultState(),
  reducer: (action, _state) =>
    switch (action) {
    | RouteInfo(classroomId, studentId, testId) =>
      ReasonReact.Update({
        ids: {
          classroomId,
          studentId,
          testId,
        },
      })
    | NoOp => ReasonReact.NoUpdate
    },
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        switch (urlToIds(url)) {
        | Some((classroomId, studentId, testId)) =>
          self.send(RouteInfo(classroomId, studentId, testId))
        | _ => self.send(NoOp)
        }
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: ({state}) =>
    <ReasonApollo.Provider client=Client.apiInstance>
      {
        switch (state.ids) {
        | _ => <MeLayout />
        }
      }
    </ReasonApollo.Provider>,
};

let default =
  ReasonReact.wrapReasonForJs(~component, _jsProps =>
    make([|
      /* ~server=(
           jsProps##server
           |> Js.undefinedToOption
           |> Belt.Option.getWithDefault(_, false)
         ), */
      /* ~initialUrl=Js.undefinedToOption(jsProps##initialUrl), */
    |])
  );