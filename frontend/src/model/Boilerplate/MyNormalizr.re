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

  module Menu = {
    type model = Menu.Model.Record.t;
    let wrap = model => `Menu(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Menu(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module MenuItem = {
    type model = MenuItem.Model.Record.t;
    let wrap = model => `MenuItem(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MenuItem(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
};


/* Can be put into normizr */

module Converter = {
  module Teacher = NormalizrSetup.DomainTypeConverter(Teacher, Teacher.Container, Wrapper.Teacher);
  module Customer = NormalizrSetup.DomainTypeConverter(Customer, Customer.Container, Wrapper.Customer);
  module Menu = NormalizrSetup.DomainTypeConverter(Menu, Menu.Container, Wrapper.Menu);
  module MenuItem = NormalizrSetup.DomainTypeConverter(MenuItem, MenuItem.Container, Wrapper.MenuItem);
};

/* module TeacherMutation = MutationNormalizr.GetRecord(Teacher.Container); */
