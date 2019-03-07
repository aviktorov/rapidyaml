#include <benchmark/benchmark.h>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/fs/fs.hpp>
#include <vector>
#include <iostream>
#include <yaml-cpp/yaml.h>


namespace bm = benchmark;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Case
{
    c4::csubstr filename;
    std::vector<char> src;
    std::vector<char> in_place;
    bool is_json;
    ryml::Tree ryml_tree;

    void load(const char* file)
    {
        filename = c4::to_csubstr(file);
        is_json = filename.ends_with(".json");
        src = c4::fs::file_get_contents<std::vector<char>>(file);
        in_place = src;
    }

};
Case c;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


void yamlcpp(bm::State& st)
{
    std::string src(c.src.begin(), c.src.end());
    for(auto _ : st)
    {
        YAML::Node node = YAML::Load(src);
    }
    st.SetBytesProcessed(st.iterations() * src.size());
}

void ryml_rw(bm::State& st)
{
    size_t sz;
    for(auto _ : st)
    {
        ryml::Tree tree = ryml::parse(c.filename, to_substr(c.in_place));
        sz = tree.size();
    }
    st.SetItemsProcessed(st.iterations() * sz);
    st.SetBytesProcessed(st.iterations() * c.in_place.size());
}

void ryml_ro(bm::State& st)
{
    size_t sz;
    for(auto _ : st)
    {
        ryml::Tree tree = ryml::parse(c.filename, to_csubstr(c.src));
        sz = tree.size();
    }
    st.SetItemsProcessed(st.iterations() * sz);
    st.SetBytesProcessed(st.iterations() * c.in_place.size());
}

void ryml_rw_reuse(bm::State& st)
{
    size_t sz;
    ryml::Parser p;
    for(auto _ : st)
    {
        c.ryml_tree.clear();
        c.ryml_tree.clear_arena();
        p.parse(c.filename, to_substr(c.in_place), &c.ryml_tree);
        sz = c.ryml_tree.size();
    }
    st.SetItemsProcessed(st.iterations() * sz);
    st.SetBytesProcessed(st.iterations() * c.in_place.size());
}

void ryml_ro_reuse(bm::State& st)
{
    size_t sz;
    ryml::Parser p;
    for(auto _ : st)
    {
        c.ryml_tree.clear();
        c.ryml_tree.clear_arena();
        p.parse(c.filename, to_csubstr(c.src), &c.ryml_tree);
        sz = c.ryml_tree.size();
    }
    st.SetItemsProcessed(st.iterations() * sz);
    st.SetBytesProcessed(st.iterations() * c.in_place.size());
}

BENCHMARK(yamlcpp);
BENCHMARK(ryml_ro);
BENCHMARK(ryml_rw);
BENCHMARK(ryml_ro_reuse);
BENCHMARK(ryml_rw_reuse);


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    bm::Initialize(&argc, argv);
    C4_CHECK(argc == 2);
    c.load(argv[1]);
    bm::RunSpecifiedBenchmarks();
}