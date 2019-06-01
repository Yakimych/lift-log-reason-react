open AppState;
open BsReactstrap;

[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

let linkElementHeight = 40;

[@react.component]
let make =
    (
      ~links: list(liftInfoLink),
      ~addLink,
      ~removeLink,
      ~changeLinkText,
      ~changeLinkUrl,
    ) => {
  let linkContainerHeight = (links |> List.length) * linkElementHeight;
  let linkElementStyle =
    ReactDOMRe.Style.make(
      ~height=string_of_int(linkElementHeight) ++ "px",
      (),
    );
  <div className="mt-2">
    <AnimateHeightWrapper
      duration=350 className="pt-1 mx--1" height=linkContainerHeight>
      {links
       |> List.mapi((index, link) =>
            <div
              className="d-flex align-items-start px-1"
              style=linkElementStyle
              key={string_of_int(index)}>
              <Input
                name="text"
                bsSize="sm"
                className="mr-3 w-50"
                value={link.text}
                placeholder="Display text"
                _type="text"
                onChange={e =>
                  changeLinkText(index, ReactEvent.Form.target(e)##value)
                }
              />
              <InputGroup>
                <Input
                  name="url"
                  bsSize="sm"
                  value={link.url}
                  placeholder="Url"
                  _type="text"
                  onChange={e =>
                    changeLinkUrl(index, ReactEvent.Form.target(e)##value)
                  }
                />
                <InputGroupAddon addonType="append">
                  <div
                    className="input-group-text remove-icon-wrapper"
                    onClick={_ => removeLink(index)}>
                    <OcticonWrapper icon={getIconByName("x")} />
                  </div>
                </InputGroupAddon>
              </InputGroup>
            </div>
          )
       |> Array.of_list
       |> ReasonReact.array}
    </AnimateHeightWrapper>
    <Button onClick={_ => addLink()} size="sm" className="mt-2">
      {ReasonReact.string("Add link")}
    </Button>
  </div>;
};
