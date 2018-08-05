#include "uml/uml.h"

struct the_diagram_t
    : uml::sequence_diagram_t
{
    explicit the_diagram_t(
        eps::iproperties_t const& parent_properties)
        : uml::sequence_diagram_t(parent_properties, 4)
    {
        lifeline_space(0, uml::grid_space * 14);
        add_simple_class(0, eps::single_line_listing(R"(main.cpp)"));
        start_lifeline(0);

        time_advance();

        start_context(0);

        time_advance(2);

        add_simple_class(1, eps::single_line_listing(R"(executor.cpp)"));
        create(0, 1, eps::single_line_listing(R"(load library)"));
        start_lifeline(1);

        time_advance(2);

        start_context(1);
        sync_message(0, 1, eps::multi_line_listing(uml::grid_space * 12, R"(execute(argc,argv,group,run_count))"));
        time_advance(2);
        add_simple_class(2, eps::single_line_listing(R"(dependency_graph_t)"));
        create(1, 2);
        start_lifeline(2);

        time_advance(2);

        add_simple_class(3, eps::single_line_listing(R"(policy_t)"));
        create(1, 3);
        start_lifeline(3);

        time_advance();

        start_context(3);
        sync_message(1, 3, eps::single_line_listing(R"(build)"));

        time_advance();

        return_message(3, 1);
        end_context(3);

        time_advance(2);

        start_context(3);
        sync_message(1, 3, eps::single_line_listing(R"(finish)"));

        time_advance();

        return_message(3, 1);
        end_context(3);

        time_advance(2);

        destroy(1, 3);
        end_lifeline(3, true);

        time_advance(2);

        destroy(1, 2);
        end_lifeline(2, true);

        time_advance();

        return_message(1, 0, eps::single_line_listing(R"(0/1/-1)"));
        end_context(1);

        time_advance();

        end_lifeline(1);
        end_context(0);

        time_advance();

        end_lifeline(0);
    }
};

int main()
{
    eps::main<the_diagram_t>(
        "cppmake_test_executor_nothing_to_build_uml_sd.eps");
}
