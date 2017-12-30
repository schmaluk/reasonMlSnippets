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

/* component */
let component = ReasonReact.reducerComponent("Root");

/* Helpers */
let str = ReasonReact.stringToElement;

let printItemStatus = itemStatus =>
  switch itemStatus {
  | Done(date) => {j|Erledigt am: $date|j}
  | Open => {j|Offen|j}
  };

let createNewItem = id => {id, itemName: "", itemStatus: Open};

let make = _children => {
  ...component,
  initialState: () => {idCounter: 0, todolist: [], newItem: createNewItem(0)},
  reducer: (action, state) =>
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
        newItem: createNewItem(newId),
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
    },
  render: self =>
    <div className="container">
      <div className="jumbotron">
        <h1> (str("Todo-App-Crap in React-Reason")) </h1>
      </div>
      <div className="row">
        <div className="col">
          <input
            _type="text"
            value=self.state.newItem.itemName
            onChange=(
              self.reduce(event =>
                UpdateNewItem(
                  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
                )
              )
            )
          />
          <button
            className="btn btn-primary" onClick=(self.reduce(e => AddNewItem))>
            (str("Add"))
          </button>
        </div>
      </div>
      <table
        className="table table-light table-striped table-bordered table-hover">
        <thead className="thead-dark">
          <tr>
            <th> (str("Item")) </th>
            <th> (str("Status")) </th>
            <th> (str("Actions")) </th>
          </tr>
        </thead>
        <tbody>
          (
            Array.of_list(self.state.todolist)
            |> Array.map(item =>
                 <tr key=(string_of_int(item.id))>
                   <td> (str(item.itemName)) </td>
                   <td> (item.itemStatus |> printItemStatus |> str) </td>
                   <td>
                     <button
                       className="btn btn-success mr-4"
                       onClick=(self.reduce(e => CloseItem(item.id)))>
                       <i className="fa fa-check-square pr-2" />
                       (str("Check"))
                     </button>
                     <button
                       className="btn btn-danger"
                       onClick=(self.reduce(e => DeleteItem(item.id)))>
                       <i className="fa fa-trash pr-2" />
                       (str("Delete"))
                     </button>
                   </td>
                 </tr>
               )
            |> ReasonReact.arrayToElement
          )
        </tbody>
      </table>
    </div>
};