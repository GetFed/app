module GraphFragment = [%graphql
  {|
    fragment teacherFields on User {
      id
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.TeacherFields;

let fragmentType = "User";