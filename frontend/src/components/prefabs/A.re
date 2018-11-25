let component = ReasonReact.statelessComponent("A");

let css = Css.css;
let tw = Css.tw;
let aClass : string = [%bs.raw
  {| css(tw`
    no-underline
  `)
|}];

let addClass = (originalClassName : string, newClassName: option(string)) =>
  switch(newClassName){
  | None => originalClassName
  | Some(newClass) => originalClassName ++ " " ++ newClass
  };

let make = (~className: option(string)=?, ~href : string, children) => {
  ...component,
  render: _self =>
    <a key="a" className=((aClass ++ " text-inherit") |> addClass(_, className)) href>
      {children |> ReasonReact.array}
    </a>
};