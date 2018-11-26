let component = ReasonReact.statelessComponent("FedFilter");

let css = Css.css;
let tw = Css.tw;

let fedFilterClass = [%bs.raw {| css(tw`
  h-full
  w-full
  bg-grey
  p-2
`)|}];

let make = (~diets:list(Diet.Model.idType), ~selectedDiet: option(Diet.Model.idType), _children) => {
  ...component,
  render: _self =>
    <div className=fedFilterClass>
      {ReasonReact.string("Filters")}
      {
        switch(selectedDiet) {
        | Some(selectedDiet) => <FedFilterDietDropdown diets selectedDiet />
        | None => <div />
        }
      }
      
      <FedFilterRestrictionSection/>
    </div>
};