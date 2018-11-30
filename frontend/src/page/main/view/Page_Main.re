let css = Css.css;
let tw = Css.tw;


type modalType =
  | LOGIN;

type state = {modal: option(modalType)};

type action =
  | NoOp
  | OpenLoginModal
  | CloseLoginModal;

let component = ReasonReact.reducerComponent("PageMain");

let make = (~pathIds, _children) => {
  ...component,
  initialState: () => {modal: None},
  reducer: (action, _state) =>
    switch (action) {
    | NoOp => ReasonReact.NoUpdate
    | OpenLoginModal => ReasonReact.Update({modal: Some(LOGIN)})
    | CloseLoginModal => ReasonReact.Update({modal: None})
    },
  render: self => {
    let closeFunction = () => self.send(CloseLoginModal);
    <Accounts>
      ...{(~accountSend, ~userId as authUserId) => {
        Js.log("authUserId = %j");
        Js.log(authUserId);
        <Modal
          modalSelect={ self.state.modal }
          closeFn=(() => closeFunction() |> ignore)
          modalContents={ modalId => {
            switch(modalId){
            | LOGIN =>
                <LoginLayout accountSend afterLoginClick=(() => self.send(CloseLoginModal)) />
            }
          } 
        }>
          <SideMenuLayout
            sideMenu=(
              <FedSideMenu
                pathIds
                accountSend
                authUserId
                openModal=(() => self.send(OpenLoginModal))
              />)
          >
            <MainPageContent key="MainPageContent" pathIds />
          </SideMenuLayout>
        </Modal>
      }}
    </Accounts>
  }
};