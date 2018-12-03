let css = Css.css;
let tw = Css.tw;

type state = {modal: option(Page_Actions.modalType)};

let component = ReasonReact.reducerComponent("PageMain");

let make = (~pathIds, _children) => {
  ...component,
  initialState: () => {modal: None},
  reducer: (action, _state) =>
    switch (action) {
    | NoOp => ReasonReact.NoUpdate
    | OpenLoginModal => ReasonReact.Update({modal: Some(Page_Actions.LOGIN)})
    | OpenSubscribeModal => ReasonReact.Update({modal: Some(Page_Actions.SUBSCRIBE)})
    | CloseModal => ReasonReact.Update({modal: None})
    },
  render: self => {
    let closeFunction = () => self.send(Page_Actions.CloseModal);
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
                <LoginLayout accountSend successClick=(() => self.send(CloseModal)) />
            | SUBSCRIBE =>
                <LoginLayout accountSend successClick=(
                  () => {
                      /* TODO This is a dirty dirty race condition */
                      ReasonReact.Router.push("/subscribe");
                      self.send(CloseModal);
                    })
                />
            }
          } 
        }>
          <SideMenuLayout
            sideMenu=(
              <FedSideMenu
                pathIds
                accountSend
                authUserId
                updateMain=((action) => self.send(action))
              />
            )
          >
            <MainPageContent key="MainPageContent" pathIds />
          </SideMenuLayout>
        </Modal>
      }}
    </Accounts>
  }
};