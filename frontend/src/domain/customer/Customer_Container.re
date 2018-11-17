let component = ReasonReact.statelessComponent("CustomerContainer");

module CustomerContainer = Customer_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <CustomerContainer fragmentType="Customer" id fragmentName="customerFields">
      ...{
           (~data) =>
             children(~customer=data |> Customer_Model.Record.fromObject)
         }
    </CustomerContainer>,
};