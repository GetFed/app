

let component = ReasonReact.statelessComponent("PlanbookLayout");

let imageStyle =
  ReactDOMRe.Style.make(~maxHeight="100%", ~maxWidth="100%", ());

let fullSize = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let flexCenter =
  ReactDOMRe.Style.make(
    ~height="100%",
    ~width="100%",
    ~display="flex",
    ~justifyContent="center",
    ~alignItems="center",
    (),
  );

let testRowsStyle = ReactDOMRe.Style.make(~border="solid 1px grey", ());

let dashboardHeaderStyle = ReactDOMRe.Style.make(~marginBottom="6em", ());

let make =
    (
      ~teacher: Teacher.Model.Record.t,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      _children,
    ) => {
  ...component,
  render: _self => {
    let updateTeacher = action =>
      MyNormalizr.Converter.Teacher.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `TeacherId(teacher.data.id),
        action,
      )
      |> updateNormalizr;

    <div style=fullSize>
      <Row>
        <ContentHeader> <h1> {ReasonReact.string("Planbook")} </h1> </ContentHeader>
      </Row>
      <Row style=dashboardHeaderStyle>
        <Col md=2>
          <img src="https://www.placecage.com/300/300" style=imageStyle />
        </Col>
        <Col md=2>
          <div style=flexCenter>
            <div>
              <h3 style=flexCenter> {ReasonReact.string("Hello,")} </h3>
              <h2 style=flexCenter> {ReasonReact.string("Nicholas")} </h2>
            </div>
          </div>
        </Col>
        <Col md=2 />
        <Col md=2>
          <TeacherCard
            title="TOTAL CLASSES"
            number={Belt.List.length(teacher.data.classroomIds)}
            textString="Lorem ipsum dolor"
          />
        </Col>
        <Col md=2>
          <TeacherCard
            title="TOTAL STUDENTS"
            number={
              teacher.data.classroomIds
              |> MyNormalizr.idListToFilteredItems(
                   _,
                   MyNormalizr.Converter.Classroom.Remote.getRecord(
                     normalized,
                   ),
                 )
              |> Belt.List.reduce(_, 0, (memo, classroom) =>
                   memo + Belt.List.length(classroom.data.studentIds)
                 )
            }
            textString="Lorem ipsum dolor"
          />
        </Col>
        <Col md=2>
          <TeacherCard
            title="TOTAL TESTS"
            number={Belt.List.length(teacher.data.testIds)}
            textString="Lorem ipsum dolor"
          />
        </Col>
      </Row>
      <Row>
        {
          Belt.List.length(teacher.data.testIds) !== 0 ?
            <Col xs=12>
              <div style=testRowsStyle>
                {
                  teacher.data.testIds
                  |> MyNormalizr.idListToFilteredItems(
                       _,
                       MyNormalizr.Converter.Test.Remote.getRecord(
                         normalized,
                       ),
                     )
                  |> Belt.List.map(_, test =>
                       <TestRow
                         key={test.data.id}
                         test
                         onClick={
                           () =>
                             updateTeacher(
                               Teacher.Action.SelectSideBar(
                                 SideTab.Test,
                                 test.data.id,
                               ),
                             )
                         }
                         normalized
                       />
                     )
                  |> Utils.ReasonReact.listToReactArray
                }
              </div>
            </Col> :
            <div />
        }
      </Row>
    </div>;
  },
};