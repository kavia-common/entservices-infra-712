#!/usr/bin/env bash
# Run static analysis (cpplint + cppcheck) for entservices-infra-712.
# This script is idempotent and safe to re-run.
# It prefers a compile_commands.json for best accuracy.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CONTAINER_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
OUT_DIR="${SCRIPT_DIR}/out"

mkdir -p "${OUT_DIR}"

echo "[INFO] Container root: ${CONTAINER_ROOT}"
echo "[INFO] Output directory: ${OUT_DIR}"

# 1) Build the file list
FILE_LIST="${OUT_DIR}/cpp_file_list.txt"
echo "[INFO] Building C/C++ file list..."
find "${CONTAINER_ROOT}" -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) > "${FILE_LIST}"
TOTAL_FILES=$(wc -l < "${FILE_LIST}" || echo 0)
echo "[INFO] Found ${TOTAL_FILES} C/C++ files."

# 2) cpplint
CPPLINT_BIN="cpplint"
if ! command -v "${CPPLINT_BIN}" >/dev/null 2>&1; then
  echo "[WARN] cpplint not found. You can install it via: pip install cpplint"
else
  echo "[INFO] Running cpplint..."
  # Filters tuned to reduce low-signal noise; adjust as needed in a CPPLINT.cfg.
  CPPLINT_FILTERS="-whitespace/tab,-legal/copyright,-build/include_subdir,-readability/todo,-whitespace/line_length"
  CPPLINT_LOG="${OUT_DIR}/cpplint_raw.txt"
  # Run command
  xargs -a "${FILE_LIST}" -I{} -r sh -c "${CPPLINT_BIN} --filter=${CPPLINT_FILTERS} \"{}\"" 2> "${CPPLINT_LOG}" || true
  echo "[INFO] cpplint complete. Log at: ${CPPLINT_LOG}"
fi

# 3) cppcheck
CPPCHECK_BIN="cppcheck"
if ! command -v "${CPPCHECK_BIN}" >/dev/null 2>&1; then
  echo "[WARN] cppcheck not found. You can install it via: sudo apt-get update && sudo apt-get install -y cppcheck"
else
  CPPCHECK_LOG="${OUT_DIR}/cppcheck_raw.txt"
  # Prefer compile_commands.json if available
  CC_DB="${CONTAINER_ROOT}/build/compile_commands.json"
  if [[ -f "${CC_DB}" ]]; then
    echo "[INFO] Running cppcheck with compile_commands.json..."
    "${CPPCHECK_BIN}" --enable=all --inline-suppr --inconclusive --std=c++17 \
      --project="${CC_DB}" 2> "${CPPCHECK_LOG}" || true
  else
    echo "[INFO] Running cppcheck in fallback mode (no compile_commands.json found at ${CC_DB})..."
    "${CPPCHECK_BIN}" --enable=all --inline-suppr --inconclusive --std=c++17 \
      --suppress=missingIncludeSystem --force \
      $(sed 's/.*/"&"/' "${FILE_LIST}" | tr '\n' ' ') \
      2> "${CPPCHECK_LOG}" || true
  fi
  echo "[INFO] cppcheck complete. Log at: ${CPPCHECK_LOG}"
fi

# 4) Brief summary
echo
echo "[SUMMARY]"
if [[ -f "${OUT_DIR}/cpplint_raw.txt" ]]; then
  CPPLINT_ISSUES=$(grep -E ':[0-9]+: ' "${OUT_DIR}/cpplint_raw.txt" | wc -l || echo 0)
  echo "cpplint issues: ${CPPLINT_ISSUES}"
else
  echo "cpplint issues: n/a (cpplint not executed)"
fi

if [[ -f "${OUT_DIR}/cppcheck_raw.txt" ]]; then
  ERRORS=$(grep -c ' error: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  WARNINGS=$(grep -c ' warning: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  INFO=$(grep -c ' information: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  STYLE=$(grep -c ' style: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  PERF=$(grep -c ' performance: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  PORT=$(grep -c ' portability: ' "${OUT_DIR}/cppcheck_raw.txt" || echo 0)
  echo "cppcheck - errors: ${ERRORS}, warnings: ${WARNINGS}, info: ${INFO}, style: ${STYLE}, performance: ${PERF}, portability: ${PORT}"
else
  echo "cppcheck: n/a (not executed)"
fi

echo
echo "[DONE] Static analysis finished. See logs in: ${OUT_DIR}"
