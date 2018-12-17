type t =
  | HOME
  | MENU
  | SUPPORT
  | GIFT
  | SUBSCRIPTION
  | ABOUT_US
  | MY_ACCOUNT;

let menuLinkToText = (menuLink: t) : string =>
  switch(menuLink){
  | HOME => "HOME"
  | MENU => "MENU"
  | SUPPORT => "SUPPORT"
  | GIFT => "GIFTS"
  | SUBSCRIPTION => "SUBSCRIPTION"
  | ABOUT_US => "ABOUT US"
  | MY_ACCOUNT => "MY ACCOUNT"
  };

let idToMenuLink = (pathIds: PathIds.t) : t =>
  switch(pathIds){
  | {myAccountId: Some(_)} => MY_ACCOUNT
  | {giftsId: Some(_)} => GIFT
  | {supportId: Some(_)} => SUPPORT
  | {menuId: Some(_)} => MENU
  | {subscriptionId: Some(_)} => SUBSCRIPTION
  | {aboutUsId: Some(_)} => ABOUT_US
  | _ => HOME
  };