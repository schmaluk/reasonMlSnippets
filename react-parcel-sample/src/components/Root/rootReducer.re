/* types */
type itemStatus =
  | Done(string)
  | Open;

type todoListItem = {
  id: int,
  itemName: string,
  itemStatus
};

/* state */
type state = {
  idCounter: int,
  todolist: list(todoListItem),
  newItem: todoListItem
};

/* actions */
type actions =
  | UpdateNewItem(string)
  | DeleteItem(int)
  | AddNewItem
  | CloseItem(int);

let initialState: todoListItem = {id: 0, itemName: "", itemStatus: Open};

let rootReducer = (action, state) =>
  switch action {
  | UpdateNewItem(itemName) =>
    Js.log("UpdateNewItem : " ++ itemName);
    let {newItem} = state;
    ReasonReact.Update({
      ...state,
      newItem: {
        ...newItem,
        itemName
      }
    });
  | DeleteItem(id) =>
    Js.log("DeleteItem : " ++ string_of_int(id));
    let {todolist, newItem} = state;
    ReasonReact.Update({
      ...state,
      todolist: List.filter(item => item.id != id, todolist)
    });
  | AddNewItem =>
    Js.log("AddNewItem");
    let {todolist, idCounter, newItem} = state;
    let newId = idCounter + 1;
    let newItem: todoListItem = {...newItem, id: newId, itemStatus: Open};
    ReasonReact.Update({
      ...state,
      newItem: {
        ...initialState,
        id: newId
      },
      idCounter: newId,
      todolist: [newItem, ...todolist]
    });
  | CloseItem(id) =>
    Js.log("CloseItem : " ++ string_of_int(id));
    let {todolist} = state;
    let todolist =
      List.map(
        item => item.id == id ? {...item, itemStatus: Done("jetzt")} : item,
        todolist
      );
    ReasonReact.Update({...state, todolist});
  | _ => ReasonReact.NoUpdate
  };