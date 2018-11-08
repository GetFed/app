type styleObj;
type tailwindFn = string => styleObj;
type emotionFn = styleObj => string;

[@bs.module "emotion"] external css: emotionFn = "css";

/* [@bs.module "tailwind.macro"] external tw: emotionFn = ""; */
/* [%bs.raw {| import tw from "tailwind.macro" |}]; */
[@bs.val] external tw: tailwindFn = "";