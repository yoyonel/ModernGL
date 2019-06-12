FROM scratch as source
COPY setup.py README.md /project/
COPY src /project/src
COPY moderngl /project/moderngl

FROM quay.io/pypa/manylinux1_i686:latest as build_i686
COPY --from=source /project .
RUN /opt/python/cp35-cp35m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl
RUN /opt/python/cp36-cp36m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl
RUN /opt/python/cp37-cp37m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl

FROM quay.io/pypa/manylinux1_x86_64:latest as build_x86_64
COPY --from=source /project .
RUN /opt/python/cp35-cp35m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl
RUN /opt/python/cp36-cp36m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl
RUN /opt/python/cp37-cp37m/bin/python setup.py bdist_wheel && auditwheel repair dist/*.whl && rm dist/*.whl

FROM alpine:3.9.4
COPY --from=build_i686 /wheelhouse/* dist/
COPY --from=build_x86_64 /wheelhouse/* dist/
CMD tar -zc dist

# docker build -t moderngl_builder -f extras/Dockerfile . && docker run --rm moderngl_builder | tar -zxv
