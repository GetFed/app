let component = ReasonReact.statelessComponent("DietButton");

let css = Css.css;
let tw = Css.tw;

let dietButtonClass = [%bs.raw {| css(tw`
  w-full
  flex
  cursor-pointer
`)|}];

let dietButtonTextClass = [%bs.raw {| css(tw`
  mr-2
`)|}];

type chevronDirection =
  | Up
  | Down
  | None;

let make = (~data as diet : Diet.Model.Record.t, ~chevron=None, ~size=FedButton.MEDIUM,  ~color=FedButton.GREY, ~onClick=((_) => ()), _children) => {
  ...component,
  render: _self =>
    <FedButton size color onClick>
      <div key="dietButton" className=dietButtonClass>
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