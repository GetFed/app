let component = ReasonReact.statelessComponent("UserLayout");

let fullSizeStyle = ReactDOMRe.Style.make(~height="100%", ());

let make = (~user: User.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div style=fullSizeStyle>
      {
        switch (user.data.teacherId) {
        | None => <AccountTypeLayout />
        | Some(teacherId) =>
          <Teacher.Container id={Schema.getUUIDFromId(teacherId)}>
            ...(
                 (~teacher) =>
                   <NormalizrInit records=[`Teacher(teacher)]>
                     ...{
                          (~normalized, ~updateNormalizr) =>
                            <TeacherLayout
                              teacherId={`TeacherId(teacher.data.id)}
                              normalized
                              updateNormalizr
                            />
                        }
                   </NormalizrInit>
               )
          </Teacher.Container>
        }
      }
    </div>,
};