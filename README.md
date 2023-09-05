# MicroPython urdflib

MicroPython urdflib contributes to the vision of the Semantic Web of Things by providing a simple
and accessible, yet lightweight library for RDF processing, based on MicroPython.

This library, named urdflib, uses [Sord](https://github.com/drobilla/sord) and
[Serd](https://github.com/drobilla/serd) as the backend, and provides an API that
conforms to the widely used [RDFLib](https://github.com/rdfLib/rdflib/) Python library,
in such a way that simple RDFLib programs could be adapted to constrained devices with
a simple change of the module import declaration:

```
import urdflib as rdflib
```

### Compatibility with RDFLib

urdflib is intended to provide users with a significant interpretation of RDFLib,
ensuring both ease of use and compatibility with existing code. This goal was achieved
by running tests using the RDFLib repository, thus allowing users to stick to the
RDFLib APIs. However, it is necessary to acknowledge that the underlying implementation
in the urdflib module is written in the C language. As of today, urdflib implements a 
coherent subset of the RDFLib API, leaving out namespaces, syntax parsers and
serializers, and other storage and querying plugins.

### Integration with the MicroPython Firmware

Three methods for creating a module in MicroPython are available: Core module, external
module, and port module. The implementation of urdflib utilizes the Sord, Serd, and Zix
C libraries, which required modifications in their code. As a result, these libraries
were merged into a single repository and added to MicroPython as an **external module**. 
Consequently, urdflib now operates as a **core module**, utilizing Serd and Sord to 
establish an API that facilitates RDF manipulation on resource-constrained devices. Two
MicroPython ports have been tested successfully: the **Unix** and the **ESP32** ports.

### How to cite

Mohsen Hadavi, Maxime Lefrançois. "The urdlib Library for MicroPython: Manipulating RDF on Constrained Devices". In _International Semantic Web Conference_. Cham: Springer International Publishing, 2023

### Acknowledgements

This work has been partly supported by a grant from the French research agency (ANR) on projects [https://coswot.gitlab.io/](CoSWot (ANR-19-CE23-0012)). 

