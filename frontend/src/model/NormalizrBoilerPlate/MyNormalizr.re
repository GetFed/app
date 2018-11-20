module Wrapper = {
  module Teacher = {
    type model = Teacher.Model.Record.t;
    let wrap = model => `Teacher(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Teacher(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Customer = {
    type model = Customer.Model.Record.t;
    let wrap = model => `Customer(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Customer(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
};

/* Can be put into normizr */

module Converter = {
  module Teacher = NormalizrSetup.DomainTypeConverter(Teacher, Teacher.Container, Wrapper.Teacher);
  module Customer = NormalizrSetup.DomainTypeConverter(Customer, Customer.Container, Wrapper.Customer);
};

/* module TeacherMutation = MutationNormalizr.GetRecord(Teacher.Container); */
