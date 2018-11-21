
type myAccountId = option(option(string));
type giftsId = option(option(string));
type supportId = option(option(string));
type menuId = option(option(string));
type adminId = option(option(string));

type t = {
  myAccountId,
  giftsId,
  supportId,
  menuId,
  adminId,
};
let default: t = {
  myAccountId: None,
  giftsId: None,
  supportId: None,
  menuId: None,
  adminId: None,
};

