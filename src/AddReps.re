open AppState;
open BsReactstrap;

[%bs.raw {|require('./AddReps.css')|}];

let component = ReasonReact.statelessComponent("AddReps");

let make =
    (
      ~dialogState: dialogState,
      ~closeDialog,
      ~changeInputMode,
      ~addLink,
      ~removeLink,
      ~changeLinkText,
      ~changeLinkUrl,
      _children,
    ) => {
  ...component,
  render: _self => {
    <Modal isOpen={dialogState.isOpen} toggle=closeDialog>

        <ModalHeader>
          {ReasonReact.string("Input sets and reps")}
        </ModalHeader>
        <ModalBody>
          <div className="px-1">
            <div className="d-flex">

                <InputModeSwitch
                  mode={dialogState.inputMode}
                  onChange=changeInputMode
                />
              </div>
              /* <div className="lead ml-4">
                   {formatRepsSets(props.setsReps)}
                 </div> */
            /* <div className="my-3">
                 {isSetsRepsMode(props) ?
                    <SetsRepsInput
                      numberOfSets={props.setsReps.numberOfSets}
                      numberOfReps={props.setsReps.numberOfReps}
                      onNumberOfSetsChange={props.onNumberOfSetsChange}
                      onNumberOfRepsChange={props.onNumberOfRepsChange}
                    /> :
                    <CustomSetsInput
                      customSetsStrings={props.setsReps.customSetsStrings}
                      canAddSet={props.canAddCustomSet}
                      onAdd={props.onAddCustomSet}
                      onRemove={props.onRemoveCustomSet}
                      onChange={props.onLiftLogRepsChange}
                    />}
               </div> */
            <div className="d-flex flex-column align-items-start">
              <Links
                links={dialogState.links}
                addLink
                removeLink
                changeLinkText
                changeLinkUrl
              />
            </div>
          </div>
        </ModalBody>
        <ModalFooter>
          <Button color="primary"> {ReasonReact.string("Save")} </Button>
          <Button color="secondary" onClick=closeDialog>
            {ReasonReact.string("Cancel")}
          </Button>
        </ModalFooter>
      </Modal>;
      /* <Button color="primary" onClick={props.onSave}> Save </Button>
         <Button color="secondary" onClick={props.close}> Cancel </Button> */
  },
};
