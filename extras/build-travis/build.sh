set -e -x

for PYBIN in /opt/python/cp3*/bin; do
    "${PYBIN}/pip" wheel /io/ -w wheelhouse/
done

for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w /io/wheelhouse/
done

# for PYBIN in /opt/python/cp3*/bin/; do
#     "${PYBIN}/pip" install moderngl --no-index -f /io/wheelhouse
# done
