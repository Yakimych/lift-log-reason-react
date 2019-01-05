open BsReactstrap;

[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

let component = ReasonReact.statelessComponent("CustomSetsInput");

let make =
    (~onAdd, ~onRemove, ~onChange, ~canAddSet, ~customSetsStrings, _children) => {
  ...component,
  render: _self =>
    <>
      <div className="d-flex flex-wrap">
        {customSetsStrings
         |> List.mapi((index, formattedSet) =>
              <div
                key={string_of_int(index)}
                className="custom-sets-input-group mr-1 mb-1">
                <InputGroup>
                  <Input
                    className="set-rep-input"
                    bsSize="sm"
                    value=formattedSet
                    onChange={e =>
                      onChange(index, ReactEvent.Form.target(e)##value)
                    }
                  />
                  {index != 0 ?
                     <InputGroupAddon addonType="append">
                       <div
                         className="input-group-text remove-icon-wrapper p-0"
                         onClick={_ => onRemove(index)}>
                         <OcticonWrapper icon={getIconByName("x")} />
                       </div>
                     </InputGroupAddon> :
                     ReasonReact.null}
                </InputGroup>
              </div>
            )
         |> Array.of_list
         |> ReasonReact.array}
      </div>
      <Button
        color="success"
        size="sm"
        className="mt-2"
        onClick=onAdd
        disabled={!canAddSet}>
        <OcticonWrapper icon={getIconByName("plus")} />
      </Button>
    </>,
};
