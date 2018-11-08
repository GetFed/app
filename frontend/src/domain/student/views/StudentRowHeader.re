let component = ReasonReact.statelessComponent("StudentRowHeader");

let fullWidthStyle =
  ReactDOMRe.Style.make(~width="100%", ~margin="0", ~padding=".5em", ());
let css = Css.css;
let tw = Css.tw;

let rowClass = [%bs.raw
  {| css(tw`flex bg-blue-lighter rounded-sm m-0 p-1 flex-wrap w-full`)|}
];
let sixthWidthClass = [%bs.raw {| css(tw` w-1/6`)|}];

let make =
    (
      ~normalized,
      ~classroom: Classroom.Model.Record.t,
      ~testIds,
      ~updateNormalizr,
      ~addStudent,
      ~addingNewStudent,
      _children,
    ) => {
  ...component,
  render: _self => {
    let selectedTest =
      switch (classroom.local.testTab) {
      | "" =>
        testIds
        |> Belt.List.head
        |> Belt.Option.mapWithDefault(_, "", Schema.getUUIDFromId)
      | a => a
      };
    let updateClassroom = action =>
      MyNormalizr.Converter.Classroom.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `ClassroomId(classroom.data.id),
        action,
      )
      |> updateNormalizr;
    <div className=rowClass>
      <div className=sixthWidthClass>
        {
          addingNewStudent ?
            <div /> : <div onClick=addStudent> <PlusIcon /> </div>
        }
      </div>
      <div className=sixthWidthClass>
        {ReasonReact.string("First Name")}
      </div>
      <div className=sixthWidthClass> {ReasonReact.string("Last Name")} </div>
      <div className=sixthWidthClass> {ReasonReact.string("Grade")} </div>
      <div className=sixthWidthClass>
        <Select
          selectedId=selectedTest
          idToString={a => a}
          selections={
            testIds
            |> MyNormalizr.idListToFilteredItems(
                 _,
                 MyNormalizr.Converter.Test.Remote.getRecord(normalized),
               )
            |> Belt.List.map(_, test =>
                 (
                   {id: test.data.id, text: test.data.name}:
                     Select.selectionType(UUID.t)
                 )
               )
          }
          onSelect={
            a =>
              updateClassroom(
                Classroom.Action.ChangeTestTab(
                  Belt.Option.getWithDefault(a, ""),
                ),
              )
          }
        />
      </div>
      <div className=sixthWidthClass />
    </div>;
  },
};