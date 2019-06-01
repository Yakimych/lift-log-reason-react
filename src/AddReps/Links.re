open AppState;
open BsReactstrap;

[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

let linkElementHeight = 40;

[@react.component]
let make =
    (
      ~links: array(liftInfoLink),
      ~addLink,
      ~removeLink,
      ~changeLinkText,
      ~changeLinkUrl,
    ) => {
  let linkContainerHeight = links->Belt.Array.length * linkElementHeight;
  let linkElementStyle =
    ReactDOMRe.Style.make(
      ~height=string_of_int(linkElementHeight) ++ "px",
      (),
    );
  <div className="mt-2">
    <AnimateHeightWrapper
      duration=350 className="pt-1 mx--1" height=linkContainerHeight>
      {links->Belt.Array.mapWithIndex((index, link) =>
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
             <InputGroupAddonWrapper addonType="append">
               <div
                 className="input-group-text remove-icon-wrapper"
                 onClick={_ => removeLink(index)}>
                 <OcticonWrapper icon={getIconByName("x")} />
               </div>
             </InputGroupAddonWrapper>
           </InputGroup>
         </div>
       )
       |> ReasonReact.array}
    </AnimateHeightWrapper>
    <Button onClick={_ => addLink()} size="sm" className="mt-2">
      {ReasonReact.string("Add link")}
    </Button>
  </div>;
};
