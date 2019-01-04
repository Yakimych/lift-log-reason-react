open AppState;

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
    <div>
      <ul>
        {links
         |> List.mapi((index, link) =>
              <li>
                {ReasonReact.string(link.text ++ ": " ++ link.url)}
                <div>
                  <input
                    value={link.text}
                    type_="text"
                    onChange={e =>
                      changeLinkText(index, ReactEvent.Form.target(e)##value)
                    }
                  />
                  <input
                    value={link.url}
                    type_="text"
                    onChange={e =>
                      changeLinkUrl(index, ReactEvent.Form.target(e)##value)
                    }
                  />
                  <button onClick={_ => removeLink(index)}>
                    {ReasonReact.string("X")}
                  </button>
                </div>
              </li>
            )
         |> Array.of_list
         |> ReasonReact.array}
      </ul>
      <button onClick={_ => addLink()}>
        {ReasonReact.string("Add link")}
      </button>
    </div>,
};
