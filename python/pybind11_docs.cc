/** Copyright 2020-2023 Alibaba Group Holding Limited.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "pybind11_docs.h"  // NOLINT(build/include_subdir)

#include <string>

namespace vineyard {
namespace doc {

const char* ObjectID = R"doc(
Opaque type for vineyard's object id. The object ID is generated by vineyard server,
the underlying type of :class:`ObjectID` is a 64-bit unsigned integer. Wrapper
utilities are provided to interact with the external python world.

.. code:: python

    >>> id = ObjectID("000043c5c6d5e646")
    >>> id
    000043c5c6d5e646
    >>> repr(id)
    '000043c5c6d5e646'
    >>> print(id)
    ObjectID <"000043c5c6d5e646">
    >>> int(id)
    74516723525190
)doc";

const char* ObjectName = R"doc(
Opaque type for vineyard's object name. ObjectName wraps a string, but it let users
know whether the variable represents a vineyard object, and do some smart dispatch
based on that. Wrapper utilities are provided to interact with the external python
world.

.. code:: python

    >>> name = ObjectName("a_tensor")
    >>> name
    'a_tensor'
    >>> repr(name)
    "'a_tensor'"
    >>> print(name)
    a_tensor
)doc";

const char* ObjectMeta = R"doc(
:class:`ObjectMeta` is the type for metadata of an :class:`Object`.
The :class:`ObjectMeta` can be treat as a *dict-like* type. If the the metadata if
the metadata obtained from vineyard, the metadata is readonly. Otherwise *key-value*
attributes or object members could be associated with the metadata to construct a
new vineyard object.

We can inspect the *key-value* attributes and members of an :class:`ObjectMeta`:

.. code:: python

    >>> meta = client.get_meta(hashmap_id)
    >>> meta
    ObjectMeta {
        "id": "0000347aebe92dd0",
        "instance_id": "0",
        ...
    }
    >>> meta['num_elements_']
    '5'
    >>> meta['entries']
    ObjectMeta {
        "id": "0000347aebe92dd0",
        "instance_id": "0",
        ...
    }

:class:`ObjectMeta` value can be iterated over:

    >>> list(k for k in meta['entries'])
    ['transient', 'num_slots_minus_one_', 'max_lookups_', 'num_elements_', 'entries_',
     'nbytes', 'typename', 'instance_id', 'id']
)doc";

const char* ObjectMeta__init__ = R"doc(
.. method:: __init__(global_: bool=False)
    :noindex:

Create an empty metadata, the metadata will be used to create a vineyard object.

Parameters
    ``global_``: bool, if the object meta is for creating a global object.
)doc";

const char* ObjectMeta_id = R"doc(
The corresponding object ID of this metadata.
)doc";

const char* ObjectMeta_signature = R"doc(
The corresponding object signature of this metadata.
)doc";

const char* ObjectMeta_typename = R"doc(
The :code:`"typename"` attribute of this metadata.
)doc";

const char* ObjectMeta_nbyte = R"doc(
The :code:`"nbytes"` attribute of this metadata.
)doc";

const char* ObjectMeta_instance_id = R"doc(
The :code:`"instance_id"` of vineyard instance that the metadata been placed on.
)doc";

const char* ObjectMeta_islocal = R"doc(
True if the object is a local object, otherwise a global object or remote object.
)doc";

const char* ObjectMeta_isglobal = R"doc(
True if the object is a global object, otherwise a local object or remote object.
)doc";

const char* ObjectMeta_set_global = R"doc(
.. method: set_global(global_: bool = true)
    :noindex:

Mark the building object as a global object.

Parameters:
    global: bool, default is True
)doc";

const char* ObjectMeta_memory_usage = R"doc(
Get the total memory usage of buffers in this object meta.
)doc";

const char* ObjectMeta__contains__ = R"doc(
.. method: __contains__(key: str) -> bool
    :noindex:

Check if given key exists in the object metadata.

Parameters:
    key: str
        The name to be looked up.

Returns:
    bool: :code:`True` if the queried key exists in this object metadata, otherwise
    :code:`False`.
)doc";

const char* ObjectMeta__getitem__ = R"doc(
.. method:: __getitem__(self, key: str) -> string or Object
    :noindex:

Get meta or member's meta from metadata.

Parameters:
    key: str
        The name to be looked up.

Returns
-------
string:
    If the given key is a key of meta, returns the meta value.
Object:
    If the given key is a key of member, return the meta of this member.
)doc";

const char* ObjectMeta_get = R"doc(
.. method:: get(self, key: str, default=None) -> string or Object
    :noindex:

Get meta or member's meta from metadata, return default value if the given key is not
presented.

Parameters:
    key: str
        The name to be looked up.

Returns
-------
str:
    When the given :code:`key` belongs to a metadata pair. Note that the metadata value
    of type int or float will be returned in string format as well.
ObjectMeta:
    When the given :code:`key` is mapped to a member object.

See Also:
    ObjectMeta.__getitem__
)doc";

const char* ObjectMeta_get_member = R"doc(
.. method:: get_member(self, key: str) -> Object
    :noindex:

Get member object from metadata, return None if the given key is not presented, and
raise exception :code:`RuntimeError` if the given key is associated with a plain
metadata, rather than member object.

Parameters:
    key: str
        The name to be looked up.

Raises:
    RuntimeError:
        When the given key is associated with a plain metadata, rather than member
        object.

See Also:
    ObjectMeta.__getitem__, ObjectMeta.get
)doc";

const char* ObjectMeta__setitem__ = R"doc(
.. method:: __setitem__(self, key: str, value) -> None
    :noindex:

Add a metadata to the ObjectMeta.

Parameters:
    key: str
        The name of the new metadata entry.

    value: str, int, float, bool or list of int
        The value of the new metadata entry.

        +  When the value is a :class:`str`, it will be convert to string at first.
        +  When the value is a list of str, int or float, it will be first dumpped
           as string using :code:`json.dumps`.

.. method:: __setitem__(self, key: str, ObjectID, Object or ObjectMeta) -> None
    :noindex:

Add a member object.

Parameters:
    key: str
        The name of the member object.
    object: :class:`Object`, :class:`ObjectID` or :class:`ObjectMeta`
        The reference to the member object or the object id of the member object.
)doc";

const char* ObjectMeta_add_member = R"doc(
.. method:: add_member(self, key: str, ObjectID, Object or ObjectMeta) -> None
    :noindex:

Add a member object.

Parameters:
    key: str
        The name of the member object.
    object: :class:`Object`, :class:`ObjectID` or :class:`ObjectMeta`
        The reference to the member object or the object id of the member object.
)doc";

const char* Object = R"doc(
Base class for vineyard objects.
)doc";

const char* Object_id = R"doc(
The object id of this object.
)doc";

const char* Object_signature = R"doc(
The object signature of this object.
)doc";

const char* Object_meta = R"doc(
The metadata of this object.
)doc";

const char* Object_nbytes = R"doc(
The nbytes of this object.
)doc";

const char* Object_typename = R"doc(
The typename of this object. :code:`typename` is the string value of the C++ type,
e.g., :code:`vineyard::Array<int>`, :code:`vineyard::Table`.
)doc";

const char* Object_member = R"doc(
.. method:: member(self, name: str) -> Object
    :noindex:

Get the member object of this object.

Parameters:
    name: str
        The name of the member object.

Returns:
    Object: The member object.

See Also:
    ObjectMeta.get, ObjectMeta.__getitem__
)doc";

const char* Object_islocal = R"doc(
Whether the object is a local object.
)doc";

const char* Object_ispersist = R"doc(
Whether the object is a persistent object. The word "persistent" means the object could
be seen by clients that connect to other vineyard server instances.
)doc";

const char* Object_isglobal = R"doc(
Whether the object is a global object.
)doc";

const char* Blob = R"doc(
:class:`Blob` in vineyard is a consecutive readonly shared memory.
)doc";

const char* Blob_size = R"doc(
Size of the blob.
)doc";

const char* Blob_is_empty = R"doc(
Whether the blob is an empty blob, i.e., the size of this blob is 0.
)doc";

const char* Blob_empty = R"doc(
Create an empty blob (with size as :code:`0`).
)doc";

const char* Blob__len__ = R"doc(
The size of this blob.
)doc";

const char* Blob_address = R"doc(
The memory address value of this blob.
)doc";

const char* BlobBuilder = R"doc(
:class:`BlobBuilder` is the builder for creating a finally immutable blob in
vineyard server.

A :class:`BlobBuilder` can only be explicitly created using the
:meth:`IPCClient.create_blob`.

See Also:
    IPCClient.create_blob
    IPCClient.create_empty_blob
)doc";

const char* BlobBuilder_id = R"doc(
ObjectID of this blob builder.
)doc";

const char* BlobBuilder__len__ = R"doc(
Size of this blob builder.
)doc";

const char* BlobBuilder_abort = R"doc(
Abort the blob builder if it is not sealed yet.
)doc";

const char* BlobBuilder_shrink = R"doc(
Shrink the blob builder to the given size if it is not sealed yet.
)doc";

const char* BlobBuilder_copy = R"doc(
.. method:: copy(self, offset: int, ptr: int, size: int, concurrency: int = 6)
    :noindex:

Copy the given address to the given offset.
)doc";

const char* BlobBuilder_address = R"doc(
The memory address value of this blob builder.
)doc";

const char* RemoteBlob = R"doc(
:class:`RemoteBlob` is a holder for :class:`Blob` in cases like the :class:`Blob`
doesn't exist in the local vineyardd instance but the client still want th access
the data with a tolerable network-transfer overhead.
)doc";

const char* RemoteBlob_id = R"doc(
Object ID of the remote blob.
)doc";

const char* RemoteBlob_instance_id = R"doc(
The instance ID where the blob is actually placed at.
)doc";

const char* RemoteBlob_is_empty = R"doc(
Whether the blob is an empty blob, i.e., the size of this blob is 0.
)doc";

const char* RemoteBlob__len__ = R"doc(
The size of this blob.
)doc";

const char* RemoteBlob_address = R"doc(
The memory address value of this blob.
)doc";

const char* RemoteBlobBuilder = R"doc(
:class:`RemoteBlobBuilder` is the builder for creating a finally immutable blob in
vineyard server over a RPC client.

A :class:`RemoteBlobBuilder` can only be explicitly initialized using
:meth:`RemoteBlobBuilder`, then be filled the content and finally be sent to remote
vineyard instance over the network.

See Also:
    IPCClient.create_blob
    IPCClient.create_empty_blob
)doc";

const char* RemoteBlobBuilderMake = R"doc(
Create a new remote blob builder with given size.

See Also:
    RemoteBlobBuilder
    RemoteBlobBuilder.wrap
)doc";

const char* RemoteBlobBuilderWrap = R"doc(
Wrap a given pointer and with its size as a remote blob builder to send to
the remote vineyard instance.

See Also:
    RemoteBlobBuilder
    RemoteBlobBuilder.make
)doc";

const char* RemoteBlobBuilderWrapBuffer = R"doc(
Wrap an existing memory buffer as a remote blob builder to send to the remote
vineyard instance.

See Also:
    RemoteBlobBuilder
    RemoteBlobBuilder.make
)doc";

const char* RemoteBlobBuilderWrapBytes = R"doc(
Wrap an existing bytes buffer as a remote blob builder to send to the remote
vineyard instance.

See Also:
    RemoteBlobBuilder
    RemoteBlobBuilder.make
)doc";

const char* RemoteBlobBuilder_size = R"doc(
Size of this blob builder.
)doc";

const char* RemoteBlobBuilder_abort = R"doc(
Abort the blob builder if it is not sealed yet.
)doc";

const char* RemoteBlobBuilder_copy = R"doc(
.. method:: copy(self, offset: int, ptr: int, size: int, concurrency: int = 6)
    :noindex:

Copy the given address to the given offset.
)doc";

const char* RemoteBlobBuilder_address = R"doc(
The memory address value of this blob builder.
)doc";

const char* InstanceStatus = R"doc(
:class:`InstanceStatus` represents the status of connected vineyard instance, including
the instance identity, memory statistics and workloads on this instance.

.. code:: python

    >>> status = client.status
    >>> print(status)
    InstanceStatus:
        instance_id: 5
        deployment: local
        memory_usage: 360
        memory_limit: 268435456
        deferred_requests: 0
        ipc_connections: 1
        rpc_connections: 0
    >>> status.instance_id
    5
    >>> status.deployment
    'local'
    >>> status.memory_usage
    360
    >>> status.memory_limit
    268435456
    >>> status.deferred_requests
    0
    >>> status.ipc_connections
    1
    >>> status.rpc_connections
    0
)doc";

const char* InstanceStatus_instance_id = R"doc(
Return the instance id of vineyardd that the client is connected to.
)doc";

const char* InstanceStatus_deployment = R"doc(
The deployment mode of the connected vineyardd cluster, can be :code:`"local"` and
:code:`"distributed"`.
)doc";

const char* InstanceStatus_memory_usage = R"doc(
Report memory usage (in bytes) of current vineyardd instance.
)doc";

const char* InstanceStatus_memory_limit = R"doc(
Report memory limit (in bytes) of current vineyardd instance.
)doc";

const char* InstanceStatus_deferred_requests = R"doc(
Report number of waiting requests of current vineyardd instance.
)doc";

const char* InstanceStatus_ipc_connections = R"doc(
Report number of alive IPC connections on the current vineyardd instance.
)doc";

const char* InstanceStatus_rpc_connections = R"doc(
Report number of alive RPC connections on the current vineyardd instance.
)doc";

const char* ClientBase = R"doc(
Base class for vineyard object builders.
)doc";

const char* ClientBase_create_metadata = R"doc(
.. method:: create_metadata(metadata: ObjectMeta) -> ObjectMeta
    :noindex:

Create metadata in vineyardd.

Parameters:
    metadata: ObjectMeta
        The metadata that will be created on vineyardd.

Returns:
    The result created metadata.

.. method:: create_metadata(metadata: ObjectMeta, instance_id: InstanceID) -> ObjectMeta
    :noindex:

Create metadata in vineyardd with a specified instance id.

Parameters:
    metadata: ObjectMeta
        The metadata that will be created on vineyardd.
    instance_id: InstanceID
        The instance to place the object metadata.

Returns:
    The result created metadata.
)doc";

const char* ClientBase_delete = R"doc(
.. method:: delete(object_id: ObjectID or List[ObjectID], force: bool = false,
                   deep: bool = true) -> None
    :noindex:

Delete the specific vineyard object.

Parameters:
    object_id: ObjectID or list of ObjectID
        Objects that will be deleted. The :code:`object_id` can be a single
        :class:`ObjectID`, or a list of :class:`ObjectID`.
    force: bool
        Forcedly delete an object means the member will be recursively deleted
        even if the member object is also referred by others. The default value
        is :code:`True`.
    deep: bool
        Deeply delete an object means we will deleting the members recursively.
        The default value is :code:`True`.

        Note that when deleting objects which have *direct* blob members, the
        processing on those blobs yields a "deep" behavior.

.. method:: delete(object_meta: ObjectMeta, force: bool = false, deep: bool = true)
                   -> None
    :noindex:

Delete the specific vineyard object.

Parameters:
    object_meta: The corresponding object meta to delete.

.. method:: delete(object: Object, force: bool = false, deep: bool = true) -> None
    :noindex:

Delete the specific vineyard object.

Parameters:
    object: The corresponding object meta to delete.
)doc";

const char* ClientBase_persist = R"doc(
.. method:: persist(object_id: ObjectID) -> None
    :noindex:

Persist the object of the given object id. After persisting, the object will be visible
by clients that connect to other vineyard server instances.

Parameters:
    object_id: ObjectID
        The object that will be persist.

.. method:: persist(object_meta: ObjectMeta) -> None
    :noindex:

Persist the given object.

Parameters:
    object_meta: ObjectMeta
        The object that will be persist.

.. method:: persist(object: Object) -> None
    :noindex:

Persist the given object.

Parameters:
    object: Object
        The object that will be persist.
)doc";

const char* ClientBase_exists = R"doc(
.. method:: exists(object_id: ObjectID) -> bool
    :noindex:

Whether the given object exists.

Parameters:
    object_id: ObjectID
        The object id to check if exists.

Returns:
    bool: :code:`True` when the specified object exists.
)doc";

const char* ClientBase_shallow_copy = R"doc(
.. method:: shallow_copy(object_id: ObjectID) -> ObjectID
    :noindex:

Create a shallow copy of the given vineyard object.

Parameters:
    object_id: ObjectID
        The vineyard object that is requested to be shallow-copied.

Returns:
    ObjectID: The object id of newly shallow-copied vineyard object.

.. method:: shallow_copy(object_id: ObjectID, extra_metadata: dict) -> ObjectID
    :noindex:

Create a shallow copy of the given vineyard object, with extra metadata.

Parameters:
    object_id: ObjectID
        The vineyard object that is requested to be shallow-copied.
    extra_metadata: dict
        Extra metadata to apply to the newly created object. The fields of extra
        metadata must be primitive types, e.g., string, number, and cannot be
        array or dict.

Returns:
    ObjectID: The object id of newly shallow-copied vineyard object.
)doc";

const char* ClientBase_put_name = R"doc(
.. method:: put_name(object: ObjectID or ObjectMeta or Object,
                     name: str or ObjectName) -> None
    :noindex:

Associate the given object id with a name. An :class:`ObjectID` can be associated with
more than one names.

Parameters:
    object_id: ObjectID
    name: str
)doc";

const char* ClientBase_get_name = R"doc(
.. method:: get_name(name: str or ObjectName, wait: bool = False) -> ObjectID
    :noindex:

Get the associated object id of the given name.

Parameters:
    name: str
        The name that will be queried.
    wait: bool
        Whether to wait util the name appears, if wait, the request will be blocked
        until the name been registered.

Return:
    ObjectID: The associated object id with the name.
)doc";

const char* ClientBase_list_names = R"doc(
.. method:: list_names(pattern: str, regex: bool = False, limit: int = 5)
                       -> Dict[str, ObjectID]
    :noindex:

List all names in current vineyard server.

Parameters:
    pattern: str
        The pattern string that will be matched against the name.
    regex: bool
        Whether the pattern is a regex expression, otherwise the pattern will be used
        as wildcard pattern. Default value is False.
    limit: int
        The limit to list. Default value is 5.

Returns:
    Dict[str, ObjectID]
)doc";

const char* ClientBase_drop_name = R"doc(
.. method:: drop_name(name: str or ObjectName) -> None
    :noindex:

Remove the association of the given name.

Parameters:
    name: str
        The name that will be removed.
)doc";

const char* ClientBase_sync_meta = R"doc(
.. method:: sync_meta() -> None
    :noindex:

Synchronize remote metadata to local immediately.
)doc";

const char* ClientBase_clear = R"doc(
.. method:: clear() -> None
    :noindex:

Drop all objects that visible to the current instance in the vineyard cluster.
)doc";

const char* ClientBase_memory_trim = R"doc(
.. method:: memory_trim() -> bool
    :noindex:

Trim the memory pool inside the shared memory allocator to return the unused
physical memory back to the OS kernel, like the `malloc_trim` API from glibc.

Returns True if it actually released any memory.
)doc";

const char* ClientBase_reset = R"doc(
.. method:: reset() -> None
    :noindex:

Alias of :meth:`ClientBase.clear`.
)doc";

const char* ClientBase_connected = R"doc(
Whether the client instance has been connected to the vineyard server.
)doc";

const char* ClientBase_instance_id = R"doc(
The instance id of the connected vineyard server.
)doc";

const char* ClientBase_meta = R"doc(
The metadata information of the vineyard server. The value is a nested dict, the
first-level key is the instance id, and the second-level key is the cluster metadata
fields.

.. code:: python

    >>> client.meta
    {
        14: {
            'hostid': '54058007061210',
            'hostname': '127.0.0.1',
            'timestamp': '6882550126788354072'
        },
        15: {
            'hostid': '48843417291806',
            'hostname': '127.0.0.1',
            'timestamp': '6882568290204737414'
        }
    }
)doc";

const char* ClientBase_status = R"doc(
The status the of connected vineyard server, returns a :class:`InstanceStatus`.

See Also:
    InstanceStatus
)doc";

const char* ClientBase_ipc_socket = R"doc(
The UNIX domain socket location of connected vineyard server.
)doc";

const char* ClientBase_rpc_endpoint = R"doc(
The RPC endpoint of the connected vineyard server.
)doc";

const char* ClientBase_version = R"doc(
The version number string of connected vineyard server, in the format of semver:
:code:`MAJOR.MINOR.PATCH`.
)doc";

const char* ClientBase_is_ipc = R"doc(
Whether the client is connected to vineyard server via UNIX domain socket.
)doc";

const char* ClientBase_is_rpc = R"doc(
Whether the client is connected to vineyard server via RPC endpoint.
)doc";

const char* IPCClient = R"doc(
IPC client that connects to vineyard instance's UNIX domain socket.
)doc";

const char* IPCClient_create_blob = R"doc(
.. method:: create_blob(size: int) -> Blob
    :noindex:

Allocate a blob in vineyard server.

Parameters:
    size: int
        The size of blob that will be allocated on vineyardd.

Returns:
    BlobBuilder
)doc";

const char* IPCClient_create_empty_blob = R"doc(
.. method:: create_empty_blob() -> Blob
    :noindex:

Create an empty blob in vineyard server.

Returns:
    Blob
)doc";

const char* IPCClient_get_blob = R"doc(
.. method:: get_blob(object_id: ObjectID, unsafe: bool = false) -> Blob
    :noindex:

Getting a blob from vineyard using the given object ID.

Parameters:
    object_id: ObjectID
        The blob to get.
    unsafe: bool
        :code:`unsafe` means getting the blob even the blob is not sealed yet.
        Default is :code:`False`.

Returns:
    Blob

See Also:
    IPCClient.get_blob
    RPCClient.get_remote_blob
    RPCClient.get_remote_blobs
)doc";

const char* IPCClient_get_blobs = R"doc(
.. method:: get_blobs(object_ids: List[ObjectID], unsafe: bool = false) -> List[Blob]
    :noindex:

Getting blobs from vineyard using the given object IDs.

Parameters:
    object_ids: List[ObjectID]
        The blobs to get.
    unsafe: bool
        :code:`unsafe` means getting the blob even the blob is not sealed yet.
        Default is :code:`False`.

Returns:
    List[Blob]

See Also:
    IPCClient.get_blobs
    RPCClient.get_remote_blob
    RPCClient.get_remote_blobs
)doc";

const char* IPCClient_get_object = R"doc(
.. method:: get_object(object_id: ObjectID) -> Object
    :noindex:

Get object from vineyard.

Parameters:
    object_id: ObjectID
        The object id to get.

Returns:
    Object
)doc";

const char* IPCClient_get_objects = R"doc(
.. method:: get_objects(object_ids: List[ObjectID]) -> List[Object]
    :noindex:

Get multiple objects from vineyard.

Parameters:
    object_ids: List[ObjectID]

Returns:
    List[Object]
)doc";

const char* IPCClient_get_meta = R"doc(
.. method:: get_meta(object_id: ObjectID, sync_remote: bool = False) -> ObjectMeta
    :noindex:

Get object metadata from vineyard.

Parameters:
    object_id: ObjectID
        The object id to get.
    sync_remote: bool
        If the target object is a remote object, :code:`code_remote=True` will force
        a meta synchronization on the vineyard server. Default is :code:`False`.

Returns:
    ObjectMeta
)doc";

const char* IPCClient_get_metas = R"doc(
.. method:: get_metas(object_ids: List[ObjectID], sync_remote: bool = False)
                      -> List[ObjectMeta]
    :noindex:

Get metadatas of multiple objects from vineyard.

Parameters:
    object_ids: List[ObjectID]
        The object ids to get.
    sync_remote: bool
        If the target object is a remote object, :code:`code_remote=True` will force
        a meta synchronization on the vineyard server. Default is :code:`False`.

Returns:
    List[ObjectMeta]
)doc";

const char* IPCClient_list_objects = R"doc(
.. method:: list_objects(pattern: str, regex: bool = False, limit: int = 5)
                         -> List[Object]
    :noindex:

List all objects in current vineyard server.

Parameters:
    pattern: str
        The pattern string that will be matched against the object's typename.
    regex: bool
        Whether the pattern is a regex expression, otherwise the pattern will be used
        as wildcard pattern. Default value is False.
    limit: int
        The limit to list. Default value is 5.

Returns:
    List[Object]
)doc";

const char* IPCClient_list_metadatas = R"doc(
.. method:: list_metadatas(pattern: str, regex: bool = False, limit: int = 5,
                           nobuffer: bool = False) -> List[Object]
    :noindex:

List all objects in current vineyard server.

Parameters:
    pattern: str
        The pattern string that will be matched against the object's typename.
    regex: bool
        Whether the pattern is a regex expression, otherwise the pattern will be
        used as wildcard pattern. Default value is False.
    limit: int
        The limit to list. Default value is 5.
    nobuffer: bool
        Whether to fill the buffers in returned object metadatas. Default value
        is False.

Returns:
    List[ObjectMeta]
)doc";

const char* IPCClient_allocated_size = R"doc(
.. method:: allocated_size(target: Object or ObjectID) -> int
    :noindex:

Get the allocated size of the given object.

Parameters:
    target: Object or ObjectID
        The given Object.

Returns:
    int
)doc";

const char* IPCClient_is_shared_memory = R"doc(
.. method:: is_shared_memory(target: ptr) -> bool
    :noindex:

Check if the address is on the shared memory region.

Parameters:
    target: address, in int format
        The given address.

Returns:
    bool
)doc";

const char* IPCClient_find_shared_memory = R"doc(
.. method:: find_shared_memory(target: ptr) -> bool
    :noindex:

Find the corresponding blob (if exists) of the given pointer.

Parameters:
    target: address, in int format
        The given address.

Returns:
    ObjectID
)doc";

const char* IPCClient_close = R"doc(
Close the client.
)doc";

const char* RPCClient = R"doc(
RPC client that connects to vineyard instance's RPC endpoints.
)doc";

const char* RPCClient_get_object = R"doc(
.. method:: get_object(object_id: ObjectID) -> Object
    :noindex:

Get object from vineyard.

Parameters:
    object_id: ObjectID
        The object id to get.

Returns:
    Object
)doc";

const char* RPCClient_get_objects = R"doc(
.. method:: get_objects(object_ids: List[ObjectID]) -> List[Object]
    :noindex:

Get multiple objects from vineyard.

Parameters:
    object_ids: List[ObjectID]

Returns:
    List[Object]
)doc";

const char* RPCClient_create_remote_blob = R"doc(
.. method:: create_remote_blob(blob_builder: RemoteBlobBuilder) -> ObjectID
    :noindex:

Put the remote blob to connected remote vineyard instance. The :code:`blob_builder`
is assumed to be ready and modification on the :code:`blob_builder` after creation
won't take effect.

Note that creating remote blobs requires network transfer and may yields significate
overhead.

.. code:: python

    vineyard_rpc_client = vineyard.connect(*vineyard_endpoint.split(':'))

    buffer_writer = RemoteBlobBuilder(len(payload))
    buffer_writer.copy(0, payload)
    blob_id = vineyard_rpc_client.create_remote_blob(buffer_writer)

Parameters:
    blob_builder: RemoteBlobBuilder
        The remote blob to create.

Returns:
    ObjectID

See Also:
    RPCClient.get_remote_blob
    RPCClient.get_remote_blobs
)doc";

const char* RPCClient_get_remote_blob = R"doc(
.. method:: get_remote_blob(object_id: ObjectID, unsafe: bool = false) -> RemoteBlob
    :noindex:

Getting a remote blob from vineyard using the given object ID.

Note that getting remote blobs requires network transfer and may yields significate
overhead.

Parameters:
    object_id: ObjectID
        The remote blob to get.
    unsafe: bool
        :code:`unsafe` means getting the blob even the blob is not sealed yet.
        Default is :code:`False`.

Returns:
    RemoteBlob

See Also:
    IPCClient.get_blob
    IPCClient.get_blobs
    RPCClient.get_remote_blobs
)doc";

const char* RPCClient_get_remote_blobs = R"doc(
.. method:: get_remote_blobs(object_ids: List[ObjectID], unsafe: bool = false)
        -> List[RemoteBlob]
    :noindex:

Getting remote blobs from vineyard using the given object IDs.

Note that getting remote blobs requires network transfer and may yields significate
overhead.

Parameters:
    object_ids: List[ObjectID]
        The remote blobs to get.
    unsafe: bool
        :code:`unsafe` means getting the blob even the blob is not sealed yet.
        Default is :code:`False`.

Returns:
    List[RemoteBlob]

See Also:
    IPCClient.get_blob
    IPCClient.get_blobs
    RPCClient.get_remote_blob
)doc";

const char* RPCClient_get_meta = R"doc(
.. method:: get_meta(object_id: ObjectID) -> ObjectMeta
    :noindex:

Get object metadata from vineyard.

Parameters:
    object_id: ObjectID
        The object id to get.

Returns:
    ObjectMeta
)doc";

const char* RPCClient_get_metas = R"doc(
.. method:: get_metas(object_ids: List[ObjectID] -> List[ObjectMeta]
    :noindex:

Get metadatas of multiple objects from vineyard.

Parameters:
    object_ids: List[ObjectID]

Returns:
    List[ObjectMeta]
)doc";

const char* RPCClient_list_objects = R"doc(
.. method:: list_objects(pattern: str, regex: bool = False, limit: int = 5)
                         -> List[Object]
    :noindex:

List all objects in current vineyard server.

Parameters:
    pattern: str
        The pattern string that will be matched against the object's typename.
    regex: bool
        Whether the pattern is a regex expression, otherwise the pattern will be
        used as wildcard pattern. Default value is False.
    limit: int
        The limit to list. Default value is 5.

Returns:
    List[Object]
)doc";

const char* RPCClient_list_metadatas = R"doc(
.. method:: list_metadatas(pattern: str, regex: bool = False, limit: int = 5,
                           nobuffer: bool = False) -> List[Object]
    :noindex:

List all objects in current vineyard server.

Parameters:
    pattern: str
        The pattern string that will be matched against the object's typename.
    regex: bool
        Whether the pattern is a regex expression, otherwise the pattern will be
        used as wildcard pattern. Default value is False.
    limit: int
        The limit to list. Default value is 5.
    nobuffer: bool
        Whether to fill the buffers in returned object metadatas. Default value
        is False.

Returns:
    List[ObjectMeta]
)doc";

const char* RPCClient_close = R"doc(
Close the client.
)doc";

const char* RPCClient_is_fetchable = R"doc(
Whether the rpc client is able to fetch objects from the connected vineyard server.
When the instance connected by the rpc client is not the same as the instance
of metadata, the rpc client is not able to fetch the object.
)doc";

const char* RPCClient_remote_instance_id = R"doc(
The instance id of the connected remote vineyard server.
)doc";

const char* connect = R"doc(
.. function:: connect(socket: str,
                      username: str = None,
                      password: str = None) -> IPCClient
    :noindex:

    Connect to vineyard via UNIX domain socket for IPC service:

    .. code:: python

        client = vineyard.connect('/var/run/vineyard.sock')

    Parameters:
        socket: str
            UNIX domain socket path to setup an IPC connection.
        username: str
            Username to login, default to None.
        password: str
            Password to login, default to None.

    Returns:
        IPCClient: The connected IPC client.

.. function:: connect(host: str,
                      port: int or str,
                      username: str = None,
                      password: str = None) -> RPCClient
    :noindex:

    Connect to vineyard via TCP socket.

    Parameters:
        host: str
            Hostname to connect to.
        port: int or str
            The TCP that listened by vineyard TCP service.
        username: str
            Username to login, default to None.
        password: str
            Password to login, default to None.

    Returns:
        RPCClient: The connected RPC client.

.. function:: connect(endpoint: (str, int or str),
                      username: str = None,
                      password: str = None) -> RPCClient
    :noindex:

    Connect to vineyard via TCP socket.

    Parameters:
        endpoint: tuple(str, int or str)
            Endpoint to connect to. The parameter is a tuple, in which the first element
            is the host, and the second parameter, can be int a str, is the port.
        username: str
            Username to login, default to None.
        password: str
            Password to login, default to None.

    Returns:
        RPCClient: The connected RPC client.

.. function:: connect(username: str = None,
                      password: str = None) -> IPCClient or RPCClient
    :noindex:

    Connect to vineyard via UNIX domain socket or TCP endpoint. This method normally
    usually no arguments, and will first tries to resolve IPC socket from the
    environment variable `VINEYARD_IPC_SOCKET` and connect to it. If it fails to
    establish a connection with vineyard server, the method will tries to resolve
    RPC endpoint from the environment variable `VINEYARD_RPC_ENDPOINT`.

    If both tries are failed, this method will raise a :class:`ConnectionFailed`
    exception.

    In rare cases, user may be not sure about if the IPC socket or RPC endpoint
    is available, i.e., the variable might be :code:`None`. In such cases this method
    can accept a `None` as arguments, and do resolution as described above.

    Parameters:
        username: str
            Username to login, default to None.
        password: str
            Password to login, default to None.

    Raises:
        ConnectionFailed
)doc";

}  // namespace doc
}  // namespace vineyard
