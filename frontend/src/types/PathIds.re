
type myAccountId = option(option(string));
type giftsId = option(option(string));
type supportId = option(option(string));
type menuId = option(option(string));
type adminId = option(option(string));
type subscriptionId = option(option(string));
type aboutUsId = option(option(string));

type t = {
  myAccountId,
  giftsId,
  supportId,
  menuId,
  adminId,
  subscriptionId,
  aboutUsId,
};
let default: t = {
  myAccountId: None,
  giftsId: None,
  supportId: None,
  menuId: None,
  adminId: None,
  subscriptionId: None,
  aboutUsId: None,
};

let stringEmptyStringOptional = (possibleEmptyString: string) : option(string) =>
  possibleEmptyString == "" ? None : Some(possibleEmptyString);

let pathToIds = (path: list(string)): t =>
  switch (path) {
  | ["my-account", myAccountId] => {...default, myAccountId: Some(stringEmptyStringOptional(myAccountId))}
  | ["my-account"] => {...default, myAccountId: Some(None)}
  | ["gifts", giftsId] => {...default, giftsId: Some(stringEmptyStringOptional(giftsId))}
  | ["gifts"] => {...default, giftsId: Some(None)}
  | ["support", supportId] => {...default, supportId: Some(stringEmptyStringOptional(supportId))}
  | ["support"] => {...default, supportId: Some(None)}
  | ["menu", menuId] => {...default, menuId: Some(stringEmptyStringOptional(menuId))}
  | ["menu"] => {...default, menuId: Some(None)}
  | ["subscribe"] => {...default, subscriptionId: Some(None)}
  | ["admin"] => {...default, adminId: Some(None)}
  | ["about-us"] => {...default, aboutUsId: Some(None)}
  | _ => default
  };

