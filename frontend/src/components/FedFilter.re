let component = ReasonReact.statelessComponent("FedFilter");

let css = Css.css;
let tw = Css.tw;

let fedFilterClass = [%bs.raw {| css(tw`
  h-full
  w-full
  bg-grey
  p-2
  flex
`)|}];

let fedFilterTextClass = [%bs.raw {| css(tw`
  mr-4
`)|}];

let make = (~diets:list(Diet.Model.idType), ~selectedDietId: option(Diet.Model.idType), _children) => {
  ...component,
  render: _self =>
    <div className=fedFilterClass>
      <div className=fedFilterTextClass>
        {ReasonReact.string("Filters")}
      </div>
      {
        Belt.Option.mapWithDefault(selectedDietId, <div/>, (selectedDietId) => {
          selectedDietId
          |> Diet.Container.getRecordById
          |> Belt.Option.mapWithDefault(_, <div/>, (selectedDiet) => {
            <FedFilterDietDropdown diets selectedDiet />
          })
        })
      }
      <FedFilterRestrictionSection/>
    </div>
};