let css = Css.css;
let tw = Css.tw;
let backgroundImageClass = [%bs.raw {| css(tw`
  w-full
  h-screen
  bg-cover
  bg-center
`)|}];

let aboutUsSubscriptionClass = [%bs.raw {| css(tw`
  h-4
`)|}];

type modalType =
  | LOGIN;

type state = {modal: option(modalType)};

type action =
  | NoOp
  | OpenLoginModal
  | CloseLoginModal;

let component = ReasonReact.reducerComponent("PageHome");

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
                  <LoginLayout accountSend afterLoginClick=(() => self.send(CloseLoginModal))
                  />
              }
            } 
          }>
            <FedSideMenu pathIds accountSend authUserId openModal=(() => self.send(OpenLoginModal)) />
            <div className=(backgroundImageClass ++ " bg-image")>
            </div>
            <div className=aboutUsSubscriptionClass/>
          </Modal>
        }
      }
    </Accounts>
  }
};