let component = ReasonReact.statelessComponent("FedFilter");

let css = Css.css;
let tw = Css.tw;

let fedFilterClass = [%bs.raw {| css(tw`
  h-12
  w-full
  bg-grey
  py-2
  px-4
  flex
`)|}];

let fedFilterTextClass = [%bs.raw {| css(tw`
  text-green-darker
  flex
  items-center
`)|}];

let fedFilterDietClass = [%bs.raw {| css(tw`
  flex
  items-center
`)|}];

let make = (~diets:list(Diet.Model.idType), ~selectedDietId: option(Diet.Model.idType), _children) => {
  ...component,
  render: _self =>
    <div className=fedFilterClass>
      <div className=fedFilterTextClass>
        {ReasonReact.string("Filters: ")}
      </div>
      <div className=fedFilterDietClass>
        {
          switch(selectedDietId){
          | Some(selectedDietId) => <FedFilterDietDropdown diets selectedDietId />
          | None => <div />
          }
        }
      </div>
      <FedFilterRestrictionSection/>
    </div>
};