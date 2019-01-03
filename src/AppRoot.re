open AppState;
open AppActions;

let component = ReasonReact.reducerComponent("AppRoot");

let make = (~testProp, _children) => {
  ...component,

  initialState: () => InitialState.getInitialState(),
  reducer: AppReducer.appReducer,

  render: self => {
    let numberOfLinksText =
      "Number of links: "
      ++ string_of_int(self.state.dialogState.links |> List.length);
    let links = self.state.dialogState.links;
    <div>
      <span> {ReasonReact.string(numberOfLinksText)} </span>
      <button onClick={_event => self.send(AddLink)}>
        {ReasonReact.string("Add link")}
      </button>
      {self.state.liftLogState.isLoading ?
         ReasonReact.string(testProp) : ReasonReact.null}
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
                        self.send(
                          ChangeLinkText(
                            index,
                            ReactEvent.Form.target(e)##value,
                          ),
                        )
                      }
                    />
                    <input
                      value={link.url}
                      type_="text"
                      onChange={e =>
                        self.send(
                          ChangeLinkUrl(
                            index,
                            ReactEvent.Form.target(e)##value,
                          ),
                        )
                      }
                    />
                    <button onClick={_ => self.send(RemoveLink(index))}>
                      {ReasonReact.string("X")}
                    </button>
                  </div>
                </li>
              )
           |> Array.of_list
           |> ReasonReact.array}
        </ul>
      </div>
    </div>;
  },
};
