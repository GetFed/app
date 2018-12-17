
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
  hidden
  md:block
  h-16
`)|}];

let mainPageContentMobileFilterButtonClass = [%bs.raw {| css(tw`
  mb-4
  block
  md:hidden
  h-16
  bg-grey
  flex
  items-center
  pl-8
  hover:bg-green-dark
`)|}];

let largeClearModalClass = [%bs.raw {| css(tw`
  block
  md:hidden
`)|}];

type state = {
  selectedDietId: option(Diet.Model.idType),
  restrictions: list(Restriction.Model.idType),
  mobileModalOpen: bool
};

type action =
  | SelectDiet(Diet.Model.idType)
  | EditRestriction(Restriction.Model.idType, bool)
  | ToggleFilterModal
  | Noop;

type modals =
  | FILTER;

let component = ReasonReact.reducerComponent("MainPageContentMenuLayout");

let make = (~diets, ~restrictions, ~currentMenu, _children) => {
  ...component,
  initialState: () => {
    selectedDietId: Belt.List.head(diets),
    restrictions: [],
    mobileModalOpen: false,
  },
  reducer: (_action, state) =>
    switch (_action) {
    | SelectDiet(selectedDiet) => {
        Diet.Container.getRecordById(selectedDiet)
        |> Belt.Option.mapWithDefault(_, ReasonReact.NoUpdate, (diet : Diet.Model.Record.t) => {
          Belt.Option.mapWithDefault(diet.data.restrictionIds, ReasonReact.NoUpdate, (restrictionIds) => {
            ReasonReact.Update({
              ...state,
              restrictions: restrictionIds |> Utils.List.removeOptionsFromList,
              selectedDietId: Some(`DietId(diet.data.id))
            });
          });
        });
      }
    | EditRestriction(changedRestrictionId, selected) => {
      ReasonReact.Update({
        ...state,
        restrictions:
          switch(selected){
          | false =>
              state.restrictions
              |> Belt.List.keep(_, (restrictionId) => restrictionId != changedRestrictionId)
          | true => state.restrictions @ [changedRestrictionId]
          }
      })
    }
    | ToggleFilterModal => ReasonReact.Update({...state, mobileModalOpen: !state.mobileModalOpen })
    | Noop => ReasonReact.NoUpdate
    },
  render: self =>
    <Modal
      modalSelect={ self.state.mobileModalOpen ? Some(FILTER): None }
      closeFn=(() => self.send(ToggleFilterModal) |> ignore)
      modalContents={
        modalId => {
          switch(modalId){
          | FILTER =>
              <FedFilterSelection
                diets
                restrictions=self.state.restrictions
                selectedDietId=self.state.selectedDietId
                updateRestriction=((restrictionId, selected) => self.send(EditRestriction(restrictionId, selected)))
                updateDiet=((dietId) => self.send(SelectDiet(dietId)))
                onSave=((_) => self.send(ToggleFilterModal))
              />
          }
        } 
    }>
      <div className=mainPageContentFedFilterClass>
        <FedFilter
          diets
          selectedDietId=self.state.selectedDietId
          restrictions=self.state.restrictions
          updateRestriction=((restrictionId, selected) => self.send(EditRestriction(restrictionId, selected)))
          updateDiet=((dietId) => self.send(SelectDiet(dietId)))
        />
      </div>
      <div className=mainPageContentMobileFilterButtonClass onClick=(_ => self.send(ToggleFilterModal))>
        {ReasonReact.string("Open Filters")}
      </div>
      <FedMenuSection restrictions=self.state.restrictions/>
    </Modal>
};