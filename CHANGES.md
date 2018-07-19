# ChangeLog

## version 2.0.0 - 2018-07-19

`dtk-core` merges both former `dtkMeta` and `dtkCore` layers.

### dtkMeta

All the former features have been retrieved.

- `dtkMetaTypeTrait` becomes `dtkCoreTypeTraits`. All the typetraits have been revisited using `c++14` features. `xtensor` coding style has been used to define the traits.
- `dtkMetaType` becomes `dtkCoreMetaType`. Static class methods have been replaced by functions in `dtk` namespace.
- `dtkMetaContainerSequential` becomes `dtkCoreMetaContainerSequential`. Registration process to QMetaType system has been simplified using `c++14` features.
- `dtkMetaContainerSequentialHandler` becomes `dtkCoreMetaContainerSequentialHandler`. Implementation has been simplified using `c++14` features.
- All the tests from `dtkMeta` have been retrieved.

### dtkCore

Some features have not been retrieved:

- `dtkArray`: it can be advantageously replaced by `xtensor`.
- `dtkAssert`: one must use `Q_ASSERT` or `Q_ASSERT_X` instead.
- `dtkCorePluginFactoryTemplate`: it is not clear that this class is still useful.
- `dtkCorePluginWidgetManager`: when necessary this class will be retrieved.
- `dtkHash`: when necessary this class will be retrieved.
- `dtkIterator`: no more necessary.
- `dtkStaticArray`: one must use `std::array` instead.
- `dtkSpinLock`: this class should be moved to `dtk-dsitributed`.

Some features have been renamed:

- `dtkApplicationPrivate` into `dtkCoreApplicationPrivate`.
- `dtkIOCompressor` into `dtkCoreIOCompressor`.
- `dtkObjectManager` into `dtkCoreObjectManager`.

Management of the `zlib` used by `dtkCoreIOCompressor` is performed via `dtkCoreConfig.h.in` file.

The other class remains unchanged:

- `dtkCoreApplication`
- `dtkCoreLayerManager`
- `dtkCorePlugin`
- `dtkCorePluginBase`
- `dtkCorePluginManager`
- `dtkCorePluginManagerHandler`
- `dtkCorePluginManagerRecorder`
- `dtkCorePluginFactory`
- `dtkCorePluginFactoryRecorder`
- `dtkCoreSettings`

`dtkCore.i` containing swig wrapping utility has been removed.

Comprehensive tests remain to be added.
