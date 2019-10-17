# ChangeLog

## version 2.7.0 - 2019-10-17
- add shareValue method in dtkCoreParameter

## version 2.6.0 - 2019-10-11
- add setter/getter on parameters for advanced
- fix for swig wrapping
- add clear on factory
- add toVariantHash method to create parameters

## version 2.5.4 - 2019-09-24
- fix bug in dtkCoreParameter : initialiser_lists methods

## version 2.5.3 - 2019-06-28
- set cmake rpath
- edit link to zlib
- add method setValues in dtkCoreParameter inlist

## version 2.5.2 - 2019-05-24
- qsettings setDefautFromat to ini
- fix bug in dtkParameter : ambiguous choice between integer 0 and null pointer

## version 2.5.1 - 2019-05-21

- fix install of dtkCoreParameters.h
- use static function instead of dtkCoreParameterReader class

## version 2.5.0 - 2019-05-21

- add dtkCoreParameterReader

## version 2.4.0 - 2019-05-17

- cmake refactoring

## version 2.3.2 - 2019-03-28

- fix install rules on windows

## version 2.3.1 - 2019-03-21

- fix build on windows

## version 2.3.0 - 2019-03-21

- add dtkParameter abstract class and implementations
- expand ~/ in path in plugin manager

## version 2.2.2 - 2018-09-19

- fix install rule of `dtkCoreRuntime`.

## version 2.2.1 - 2018-09-19

- add `unload` method in `dtkCorePluginManager`.

## version 2.2.0 - 2018-07-20

- Retrieves `dtkCorePluginWidgetManager`. It is necessary for `dtk-composer`.

## version 2.1.0 - 2018-07-20

- Add overloads of debug operators in `dtkCoreMetatype`. It is necessary for `dtk-composer`.

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
