let component = ReasonReact.statelessComponent("LoginLayout");

let css = Css.css;
let tw = Css.tw;
let loginLayoutClass = [%bs.raw
  {| css(tw` bg-green h-64`)|}
];

let make = (_children) => {
  ...component,
  render: _self => {
    Js.log("hello login layout");
    Js.log("Accounts.accountClient");
    Js.log(Accounts.accountClient);
    Js.log();
    <div className=loginLayoutClass >
      <div/>
    </div>}
};