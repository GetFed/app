type modalType =
  | LOGIN
  | SUBSCRIBE;

type action =
  | NoOp
  | OpenLoginModal
  | OpenSubscribeModal
  | CloseModal;