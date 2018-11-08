let component = ReasonReact.statelessComponent("LoginLayout");

let css = Css.css;
let tw = Css.tw;

let loginInterClassname = [%bs.raw {| css(tw` w-full text-white p-8 `)|}];
let gridClass = [%bs.raw {| css(tw` flex flex-wrap`)|}];
let tiroClass = [%bs.raw {| css(tw` w-full sm:w-full md:w-1/3 l:w/6  `)|}];
let lineClass = [%bs.raw
  {| css(tw` w-full border-0 border-b border-white border-solid mb-8 `) |}
];

let tiroIntroLeftClass = [%bs.raw {| css(tw` w-full sm:w-full md:w-1/2  `) |}];
let tiroIntroMiddleClass = [%bs.raw
  {| css(tw` w-full sm:w-full md:w-1/6  `) |}
];
let tiroIntroRightClass = [%bs.raw
  {| css(tw` w-full sm:w-full md:w-1/3  `) |}
];

let whiteSectionClass = [%bs.raw {| css(tw` bg-white  `) |}];

let smallTextClass = [%bs.raw {| css(tw`mb-2`) |}];

let mainTextClass = [%bs.raw {| css(tw` text-5xl leading-none mb-6 `) |}];

let iconClass = [%bs.raw {| css(tw` w-full sm:w-full md:w-1/3 py-8 `) |}];

let bottomMargin = ReactDOMRe.Style.make(~marginBottom="2em", ());

let footerClass = [%bs.raw {| css(tw` flex justify-center my-2 `) |}];

let tiroStyle = ReactDOMRe.Style.make(~display="flex", ());

let make = _children => {
  ...component,
  render: _self =>
    <LoginBackground>
      <div className=loginInterClassname>
        <div className=gridClass>
          <div className=tiroClass> <TiroLogo style=tiroStyle /> </div>
        </div>
        <div className=gridClass> <div className=lineClass /> </div>
        <div className=gridClass>
          <div className=tiroIntroLeftClass>
            <div className=mainTextClass>
              {
                ReasonReact.string(
                  "Welcome to our tiro online testing community",
                )
              }
            </div>
            <div className=smallTextClass>
              {
                ReasonReact.string(
                  "Tiro helps teachers build tests and grade them fairly.",
                )
              }
            </div>
            <div className=smallTextClass>
              {
                ReasonReact.string(
                  "Build real learning experiences and open doors.",
                )
              }
            </div>
          </div>
          <div className=tiroIntroMiddleClass />
          <div className=tiroIntroRightClass> <GoogleLoginButton /> </div>
        </div>
      </div>
      <div className=whiteSectionClass>
        <div className=gridClass>
          <div className=iconClass>
            <IconText
              icon={<ConnectdevelopIcon />}
              text="Something to write here that gives a quick little one liner about this title"
            />
          </div>
          <div className=iconClass>
            <IconText
              icon={<FileAltIcon />}
              text="Something to write here that gives a quick little one liner about this title"
            />
          </div>
          <div className=iconClass>
            <IconText
              icon={<SearchIcon />}
              text="Something to write here that gives a quick little one liner about this title"
            />
          </div>
        </div>
      </div>
      <div className=loginInterClassname>
        <div className=footerClass>
          {
            ReasonReact.string(
              "We never sell information personal or pertaining to individuals in any way of those listed in Real & Open",
            )
          }
        </div>
      </div>
    </LoginBackground>,
};