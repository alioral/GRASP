<h2>Greedy Randomized Adaptive Search Procedure</h2>

<p>This project is an alternative I've developed over reading a few articles, based on finding cliques applying multiple selection techniques such as <b>greedy</b> and <b>randomized</b></p>
<p>By the nature of my implementation, GRASP is used for finding A clique (not the clique with maximum size), by applying the steps below;</p>
<p>
<ul>
    <li>Select a random clique</li>
    <li>List its neighbors by taking a <b>cardinality parameter</b> into consideration*</li>
    <li>From selected nodes obtain the top x% (x verifies depending on the size of the graph)</li>
    <li>Obtain the sublist constructed by the x% of nodes and pick a <b>random</b> node between them.</li>
     <li>Verify if the selected node has a connection with each node in possible solution set.If it is, add to the solution set, if not pick another one.</li>
     <li>Proceed this until no node can be found with the proper qualifications. Later on terminate the program.</li>
</ul>
</p>
<p><b>*</b>: Since my project involved working with graphs that only contains minimal information (Node #1, Node #2) I've come up with using the <b>weight</b> between two nodes as my cardinality parameter.</p>
<p>The file <b>testGraph.txt</b> can be an example for what kind of input the program requires.</p>