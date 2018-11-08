let component = ReasonReact.statelessComponent("TestBuilderContentSection");
let css = Css.css;
let tw = Css.tw;

let testBuilderContentFullClass = [%bs.raw
  {| css(tw` h-full w-full p-0 m-0`)|}
];

let testBuilderInternalContentClass = [%bs.raw
  {| css(tw` h-full w-full border-0 border-r border-grey border-solid pr-4 `)|}
];

let make = (~sidebar, children) => {
  ...component,
  render: _self =>
    <div className=testBuilderContentFullClass>
      <Row className=testBuilderContentFullClass>
        <Col md=10 orderMd=1 xs=12 orderXs=2>
          {
            ReasonReact.createDomElement(
              "div",
              ~props={"className": testBuilderInternalContentClass},
              children,
            )
          }
        </Col>
        <Col md=2 orderMd=2 xs=12 orderXs=1> sidebar </Col>
      </Row>
    </div>,
};