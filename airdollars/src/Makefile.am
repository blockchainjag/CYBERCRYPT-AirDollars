DIST_SUBDIRS = secp256k1

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

AIRDOLLARS_CONFIG_INCLUDES=-I$(builddir)/config
AIRDOLLARS_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

AIRDOLLARS_INCLUDES += -I$(srcdir)/secp256k1/include

LIBAIRDOLLARS_SERVER=libairdollars_server.a
LIBAIRDOLLARS_WALLET=libairdollars_wallet.a
LIBAIRDOLLARS_COMMON=libairdollars_common.a
LIBAIRDOLLARS_CLI=libairdollars_cli.a
LIBAIRDOLLARS_UTIL=libairdollars_util.a
LIBAIRDOLLARS_CRYPTO=crypto/libairdollars_crypto.a
LIBAIRDOLLARS_UNIVALUE=univalue/libairdollars_univalue.a
LIBAIRDOLLARSQT=qt/libairdollarsqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libairdollars_crypto.a \
  libairdollars_util.a \
  libairdollars_common.a \
  univalue/libairdollars_univalue.a \
  libairdollars_server.a \
  libairdollars_cli.a
if ENABLE_WALLET
AIRDOLLARS_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libairdollars_wallet.a
endif

if BUILD_AIRDOLLARS_LIBS
lib_LTLIBRARIES = libairdollarsconsensus.la
LIBAIRDOLLARS_CONSENSUS=libairdollarsconsensus.la
else
LIBAIRDOLLARS_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_AIRDOLLARSD
  bin_PROGRAMS += airdollarsd
endif

if BUILD_AIRDOLLARS_UTILS
  bin_PROGRAMS += airdollars-cli airdollars-tx
endif

.PHONY: FORCE
# airdollars core #
AIRDOLLARS_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libairdollars_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between airdollarsd and airdollars-qt
libairdollars_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libairdollars_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairdollars_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(JSON_H) \
  $(AIRDOLLARS_CORE_H)

# wallet: shared between airdollarsd and airdollars-qt, but only linked
# when wallet enabled
libairdollars_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
libairdollars_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairdollars_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(AIRDOLLARS_CORE_H)

# crypto primitives library
crypto_libairdollars_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_CONFIG_INCLUDES)
crypto_libairdollars_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libairdollars_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# univalue JSON library
univalue_libairdollars_univalue_a_CPPFLAGS = $(AM_CPPFLAGS)
univalue_libairdollars_univalue_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
univalue_libairdollars_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue.h \
  univalue/univalue_escapes.h \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp

# common: shared between airdollarsd, and airdollars-qt and non-server tools
libairdollars_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
libairdollars_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairdollars_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(AIRDOLLARS_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libairdollars_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
libairdollars_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairdollars_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(AIRDOLLARS_CORE_H)

if GLIBC_BACK_COMPAT
libairdollars_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between airdollars-cli and airdollars-qt
libairdollars_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
libairdollars_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairdollars_cli_a_SOURCES = \
  rpcclient.cpp \
  $(AIRDOLLARS_CORE_H)

nodist_libairdollars_util_a_SOURCES = $(srcdir)/obj/build.h
#

# airdollarsd binary #
airdollarsd_SOURCES = airdollarsd.cpp
airdollarsd_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
airdollarsd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
airdollarsd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
airdollarsd_SOURCES += airdollarsd-res.rc
endif

airdollarsd_LDADD = \
  $(LIBAIRDOLLARS_SERVER) \
  $(LIBAIRDOLLARS_COMMON) \
  $(LIBAIRDOLLARS_UNIVALUE) \
  $(LIBAIRDOLLARS_UTIL) \
  $(LIBAIRDOLLARS_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
airdollarsd_LDADD += libairdollars_wallet.a
endif

airdollarsd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# airdollars-cli binary #
airdollars_cli_SOURCES = airdollars-cli.cpp
airdollars_cli_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
airdollars_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
airdollars_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
airdollars_cli_SOURCES += airdollars-cli-res.rc
endif

airdollars_cli_LDADD = \
  $(LIBAIRDOLLARS_CLI) \
  $(LIBAIRDOLLARS_UTIL)

airdollars_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# airdollars-tx binary #
airdollars_tx_SOURCES = airdollars-tx.cpp
airdollars_tx_CPPFLAGS = $(AM_CPPFLAGS) $(AIRDOLLARS_INCLUDES)
airdollars_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
airdollars_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
airdollars_tx_SOURCES += airdollars-tx-res.rc
endif

airdollars_tx_LDADD = \
  $(LIBAIRDOLLARS_UNIVALUE) \
  $(LIBAIRDOLLARS_COMMON) \
  $(LIBAIRDOLLARS_UTIL) \
  $(LIBAIRDOLLARS_CRYPTO) \
  $(LIBSECP256K1)

airdollars_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# airdollarsconsensus library #
if BUILD_AIRDOLLARS_LIBS
include_HEADERS = script/airdollarsconsensus.h
libairdollarsconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/airdollarsconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libairdollarsconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libairdollarsconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libairdollarsconsensus_la_LIBADD = $(CRYPTO_LIBS)
libairdollarsconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_AIRDOLLARS_INTERNAL
libairdollarsconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
