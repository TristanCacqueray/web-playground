# A playground for functional web interfaces

This project hosts different implementation for a fake service.

The demo interface is composed of:

* List of links
* A login/logout button
* A list of object that admin can delete

The service api is:

* `GET /api/info` returns the list of links `{name: Text, path: Text}` in `{services: []}`
* `POST /api/login` login
  * Input is `{login: Text, password: Text}`
  * Output `200` on success with a `{token: Text}`
  * Output `404` on failure
* `PUT /api/logout` logout
* `GET /api/resources` returns list of object `{id: Natural, name: Text}`
* `DELETE /api/resources/id` deletes an object, only admin can do that
