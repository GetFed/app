let component = ReasonReact.statelessComponent("MainPageContentMenu");

let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
`)|}];
let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      <div className=mainPageContentFedFilterClass>
        <FedFilter />
      </div>
      <FedMenuSection />
    </div>,
};