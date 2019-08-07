open ReasonReactElmish;

module Config = {
  type message =
    | SetName(string);

  type model = {
    weight: float,
    name: string,
  };

  let update = (model, message) => {
    switch (message) {
    | SetName(newName) => ({...model, name: newName}, None)
    };
  };

  let initialState = ({name: "blank", weight: 0.0}, None);
};

include Elmish.Make({
  type model = Config.model;

  type message = Config.message;

  let update = Config.update;
  let storeEnhancer = None;
  let initialState = Config.initialState;
});
