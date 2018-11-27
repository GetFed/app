let component = ReasonReact.statelessComponent("DietButton");

let css = Css.css;
let tw = Css.tw;

let dietButtonClass = [%bs.raw {| css(tw`
  w-full
  flex
`)|}];

let dietButtonTextClass = [%bs.raw {| css(tw`
  mr-2
`)|}];

type chevronDirection =
  | Up
  | Down
  | None;

let make = (~data as diet : Diet.Model.Record.t, ~chevron=None, ~onClick=((_) => ()), _children) => {
  ...component,
  render: _self =>
    <FedButton onClick>
      <div className=dietButtonClass>
        <div className=dietButtonTextClass>
          {ReasonReact.string(diet.data.name)}
        </div>
        {
          switch(chevron){
          | Up => <div />
          | Down => <ChevronDownIcon />
          | None => <div />
          }
        }
      </div>
    </FedButton>
};