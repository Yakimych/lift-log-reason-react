open AppState;
open BsReactstrap;

[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

let component = ReasonReact.statelessComponent("Links");

let make =
    (
      ~links: list(liftInfoLink),
      ~addLink,
      ~removeLink,
      ~changeLinkText,
      ~changeLinkUrl,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className="mt-2">
      {links
       |> List.mapi((index, link) =>
            <div
              className="d-flex align-items-start px-1"
              key={string_of_int(index)}>
              {ReasonReact.string(link.text ++ ": " ++ link.url)}
              <Input
                name="text"
                bsSize="sm"
                className="mr-3 w-50"
                value={link.text}
                placeholder="Display text"
                type_="text"
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
                  type_="text"
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
      <Button onClick={_ => addLink()} size="sm" className="mt-2">
        {ReasonReact.string("Add link")}
      </Button>
    </div>,
};
